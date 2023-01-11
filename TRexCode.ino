#include <LiquidCrystal.h>
#include <Arduino.h>
#define PRLN(x) Serial.println(x)
#define PR(x) Serial.print(x); Serial.print(" ")


/*
13 12 11 10 9 8  7 6
12 13 8  G  # 11 7 3.3 
*/

LiquidCrystal lcd(49, 47, 48, 46, 44, 42);

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
int high_score = 0;

int select_but = 0, enter_but = 0, last_sample = 0;
const int SAMPLE_PERIOD = 50;

int level = 1, speed = 1;

int RBG[3] = {2, 3, 4};
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

  sample();
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
  printScore();

  while (isShowScore) {
    sample();
    if (select_but || enter_but){
      isShowScore = false;
    }
    delay(300);
  }
}

void printScore()
{
  lcd.clear();
  lcd.print(high_score);
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

  int random_bullet = random(8, 14);
  int bullet_on_air = random(0, 2);

  const int columnValueToStopMoveTrees = -(secondPosition + thirdPosition);

  // this loop is to make the trees move, this loop waiting until
  // all the trees moved
  for (; firstTreePosition >= columnValueToStopMoveTrees; firstTreePosition--) {

    defineDinoPosition();
    //display dino
    enter_but ? putDinoOnGround() : putDinoOnAir();

    score++;
    speed = 200 - score;
    speed = speed < 70 ? 70 - int(score / 20) : speed;
    int k = speed < 70 ? 70 : speed;
    int small_delay = map (k, 70, 201, 1, 10);
    // score : 70 -> 250
    // delay : 1 -> n

    lcd.setCursor(14, 0);
    lcd.print(map(201-speed, 0, 201, 1, 50));

    int secondTreePosition = firstTreePosition + secondPosition;
    int thirdTreePosition = secondTreePosition + thirdPosition;
    int tree_pos[] = {
      firstTreePosition,
      secondTreePosition,
      thirdTreePosition,
    };

    if (bullet_on_air)
    {
      bulletOnAir(random_bullet);
    }
    else
    {
      bulletOnGround(random_bullet);
    }
    random_bullet-=1;

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
      if (bullet_on_air == 0) check = check || (random_bullet == 1);
    } else {
      for (int i = 0; i < 3; i++) {
        if (tree_on_air[i] == 1) {
          check = check || (tree_pos[i] == 1);
        }
      }
      if (bullet_on_air) check = check || (random_bullet == 1);
    }

    if (check)
    {
      int air = isDinoOnGround;
      for (int i = 0; i < 6; i++)
      {
        lcd.setCursor(1, air);
        lcd.write(DINO_CHAR);
        if (isDinoOnGround) {
          if (random_bullet == 1) {
            bulletOnGround(2);
          } else{
            showTree(2);
          }
        } else {
          if (random_bullet == 1) {
            bulletOnAir(2);
          } else{
          showTreeOnAir(2);
          }
        }
        delay(100);
        lcd.setCursor(1, air);
        lcd.print(" ");
        if (isDinoOnGround) {
          if (random_bullet == 1) {
            bulletOnGround(2);
          } else{
            showTree(2);
          }
        } else {
          if (random_bullet == 1) {
            bulletOnAir(2);
          } else{
          showTreeOnAir(2);
          }
        }
        delay(100);
      }
      handleGameOver();
      break;
    }
    
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
  high_score = high_score > score ? high_score : score;
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