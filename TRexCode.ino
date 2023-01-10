#include <LiquidCrystal.h>
#include <Arduino.h>
#define PRLN(x) Serial.println(x)
#define PR(x) Serial.print(x); Serial.print(" ")


// 12 -> 21
// 11 20
// 5 19
// 4 18
// 3 17
// 2 16

// 13 9
// 12 8

// Defines the pins that will be used for the display
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

LiquidCrystal lcd(52, 50, 48, 46, 44, 42);

//bitmap array for the dino character
byte dino[] = {
  B00000,
  B00111,
  B00101,
  B10111,
  B11100,
  B11111,
  B01101,
  B01100,
};

byte bullet[] = {
  B00000,
  B00011,
  B00111,
  B01110,
  B11100,
  B01110,
  B00111,
  B00011,
};

//character for the tree
byte tree[] = {
  B00011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11111,
  B01110,
  B01110
};

const int BUTTON_ENTER = 22;
const int BUTTON_SELECT = 24;

const int MENU_SIZE = 2;
const int LCD_COLUMN = 16;

const int TREE_CHAR = 6;
const int DINO_CHAR = 7;
const int BULLET_CHAR = 8;

boolean isPlaying = false;
boolean isShowScore = false;
boolean isDinoOnGround = true;

int currentIndexMenu = 0;
int score = 0;
int scoreListSize = 0;
String scoreList[20];

int select_but = 0, enter_but = 0, last_sample = 0;
const int SAMPLE_PERIOD = 50;

int level = 1, speed = 1;

int RBG[3] = {5, 6, 7};
int VAL_RBG[3] = {0, 0, 0};
int TMP = 0;
void rgb_reset() {
    for (int i = 0; i < 3; i++) {
      // PR(VAL_RBG[i]);
      // PR(" ");
        analogWrite(RBG[i], 0);
    }
}

void rgb_update() {
    TMP++;
    float angle = radians(TMP);
    int MAX_BRIGHTNESS = 50; // I prefer 50 but default -> 255;
    for (int i = 0; i < 3; i++) {
        float brightness = (MAX_BRIGHTNESS / 2) + (MAX_BRIGHTNESS / 2) * sin(angle + i * 120);
        VAL_RBG[i] = (int) brightness;
    }
}

void rgb_show() {
    for (int i = 0; i < 3; i++) {
      // PR(VAL_RBG[i]);
      // PR(" ");
        analogWrite(RBG[i], VAL_RBG[i]);
    // PRLN(" | ");
    }
}

void sample()
{
    if (millis() - last_sample > SAMPLE_PERIOD)
    {
        select_but = digitalRead(BUTTON_SELECT);
        enter_but = digitalRead(BUTTON_ENTER);
        last_sample = millis();
    }
}

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(DINO_CHAR, dino);
  lcd.createChar(TREE_CHAR, tree);
  lcd.createChar(BULLET_CHAR, bullet);

  pinMode(RBG[0], OUTPUT);
  pinMode(RBG[1], OUTPUT);
  pinMode(RBG[2], OUTPUT);

  Serial.begin(9600);
  pinMode(BUTTON_ENTER, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
}

void loop() {
  rgb_update();
  lcd.clear();
  // delay(10);
  handleMenu();
  delay(100);
}

void handleMenu() {
  String menu[MENU_SIZE] = { "START", "SCORE" };

  for (int i = 0; i < MENU_SIZE; i++) {
    if (i == currentIndexMenu) {
      lcd.setCursor(0, i);
      lcd.print("-> ");
    }

    lcd.setCursor(3, i);
    lcd.print(menu[i]);
  }
  // PR("select_but: ");
  // PRLN(select_but);
  // PRLN(enter_but);
  sample();
  // PR("show: ");
  // PRLN(select_but);
  // PRLN(enter_but);

  if (select_but == 0){
    currentIndexMenu = currentIndexMenu == 0 ? 1 : 0;
    delay(200);
  }

  if (enter_but == 0){
    currentIndexMenu == 0 ? startGame() : showScore();
  }
}

void showScore() {
  isShowScore = true;
  delay(200);

  int currentIndex = 0;
  const int lastIndex = scoreListSize - 1;

  printScore(currentIndex, lastIndex);

  while (isShowScore) {
    sample();
    if (select_but){
      currentIndex = currentIndex < lastIndex ? currentIndex + 1 : 0;
      printScore(currentIndex, lastIndex);
    }

    if (enter_but){
      isShowScore = false;
    }

    delay(300 );
  }
}

void printScore(int index, int lastIndex) {
  lcd.clear();

  if (lastIndex == -1) {
    lcd.print("NO SCORE");
  } else {
    lcd.print(scoreList[index]);

    if (index < lastIndex) {
      lcd.setCursor(0, 1);
      lcd.print(scoreList[index + 1]);
    }
  }
}

void startGame() {
  isPlaying = true;

  while (isPlaying) {
    handleGame();
  }
}

void handleGame() {
  lcd.clear();

  int buttonPressedTimes = 0;

  // Generate two random distances for the space between the trees
  int secondPosition = random(4, 9);
  int thirdPosition = random(4, 9);
  int firstTreePosition = LCD_COLUMN;
  int tree_on_air [] = {
    random(0, 2),
    random(0, 2),
    random(0, 2),
  };

  int random_bullet = random(8, 13);
  int bullet_on_air = random(0, 2);

  const int columnValueToStopMoveTrees = -(secondPosition + thirdPosition);

  // this loop is to make the trees move, this loop waiting until
  // all the trees moved
  for (; firstTreePosition >= columnValueToStopMoveTrees; firstTreePosition--) {
    // rgb_update();

    if (bullet_on_air) {
      bulletOnAir(random_bullet);
    } else {
      bulletOnGround(random_bullet);
    }
    random_bullet-=1;

    defineDinoPosition();

    int secondTreePosition = firstTreePosition + secondPosition;
    int thirdTreePosition = secondTreePosition + thirdPosition;
    int tree_pos[] = {
      firstTreePosition,
      secondTreePosition,
      thirdTreePosition,
    };
    
    for (int i = 0; i < 3; i++) {
      if (tree_on_air[i] == 1) {
        showTreeOnAir(tree_pos[i]);
      } else {
        showTree(tree_pos[i]);
      }
    }

    int check = 0;
    if (isDinoOnGround) {
      for (int i = 0; i < 3; i++) {
        if (tree_on_air[i] == 0) {
          check = check || (tree_pos[i] == 1);
        }
      }
    } else {
      for (int i = 0; i < 3; i++) {
        if (tree_on_air[i] == 1) {
          check = check || (tree_pos[i] == 1);
        }
      }
    }

    if (check)
    {
      int air = isDinoOnGround;
      for (int i = 0; i < 6; i++)
      {
        lcd.setCursor(1, air);
        lcd.write(DINO_CHAR);
        if (isDinoOnGround) {
          showTree(2);
        } else {
          showTreeOnAir(2);
        }
        delay(100);
        lcd.setCursor(1, air);
        lcd.print(" ");
        if (isDinoOnGround)
        {
          showTree(2);
        }
        else
        {
          showTreeOnAir(2);
        }
        delay(100);
      }
      // delay(1000); 
      handleGameOver();
      break;
    }

    score++;
    speed = 200 - score;
    speed = speed < 70 ? 70 - int(score / 20) : speed;
    int k = speed < 70 ? 70 : speed;
    int small_delay = map (k, 70, 201, 1, 10);
    // score : 70 -> 250
    // delay : 1 -> n

    //display dino
    enter_but ? putDinoOnGround() : putDinoOnAir();

    lcd.setCursor(13, 0);
    lcd.print(map(201-speed, 0, 201, 1, 50));
    
    while (speed >= 0) {
      rgb_update();
      rgb_show();
      delay(small_delay);
      speed -= small_delay;
    }

    // delay(speed);
  }
}

void handleGameOver() {
  lcd.clear();
  lcd.print("GAME OVER");

  lcd.setCursor(0, 1);
  lcd.print("SCORE: ");
  lcd.print(score);

  delay(3000);
  saveScore();
}

void saveScore() {
  lcd.clear();
  scoreList[scoreListSize] = score;
  scoreListSize++;

  isPlaying = false;
  score = 0;
  handleMenu();
}

void showTree(int position) {
  lcd.setCursor(position, 1);
  lcd.write(TREE_CHAR);

  // clean the previous position
  lcd.setCursor(position + 1, 1);
  lcd.print(" ");
}

void showTreeOnAir(int position) {
  lcd.setCursor(position, 0);
  lcd.write(TREE_CHAR);

  // clean the previous position
  lcd.setCursor(position +1, 0);
  lcd.print(" ");
}

void defineDinoPosition() {
  sample();
}

void putDinoOnGround() {
  lcd.setCursor(1, 1);
  lcd.write(DINO_CHAR);
  lcd.setCursor(1, 0);
  lcd.print(" ");

  isDinoOnGround = true;
}

void putDinoOnAir() {
  lcd.setCursor(1, 0);
  lcd.write(DINO_CHAR);
  lcd.setCursor(1, 1);
  lcd.print(" ");

  isDinoOnGround = false;
}


void bulletOnGround(int pos) {
  lcd.setCursor(pos, 1);
  lcd.write(BULLET_CHAR);
  lcd.setCursor(pos+1, 1);
  lcd.print(" ");
}

void bulletOnAir(int pos) {
  lcd.setCursor(pos, 0);
  lcd.write(BULLET_CHAR);
  lcd.setCursor(pos+1, 0);
  lcd.print(" ");
}