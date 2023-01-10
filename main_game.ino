#define PRLN(x) Serial.println(x)
#define PR(x) Serial.print(x); Serial.print(" ")

#include <LiquidCrystal.h>

typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;

    int (*TickFct)(int);
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];


LiquidCrystal lcd(21, 20, 19, 18, 17, 16);

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

const int BUTTON_ENTER = 12;
const int BUTTON_SELECT = 13;

const int MENU_SIZE = 2;
const int LCD_COLUMN = 16;

const int TREE_CHAR = 6;
const int DINO_CHAR = 7;

boolean isDinoOnGround = true;

int currentIndexMenu = 0;
int score = 0;
int scoreListSize = 0;
String scoreList[20];

int select, enter;
unsigned long last_sample;
int const SAMPLE_PERIOD = 200;

void sample()
{
    if (millis() - last_sample > SAMPLE_PERIOD)
    {
        select = digitalRead(BUTTON_SELECT);
        enter = digitalRead(BUTTON_ENTER);
        last_sample = millis();
    }
}

enum SM1 {
    INIT, ON, OFF, PAUSE,
};

int SM1_Tick(int state1) {
    sample();
    switch (state1) { // State transitions
    case INIT:
        state1 = ON;
        break;

    case ON:
        PRLN(state1);
        show_menu();

        break;

    case OFF:
        break;
    }

    switch (state1) { // State Action
    case INIT:
        break;

    case ON:
        break;

    case OFF:
        break;
    }
    return state1;
}


void setup() {
    // pinMode(YELLOW, OUTPUT);
    lcd.begin(16, 2);
    lcd.createChar(DINO_CHAR, dino);
    lcd.createChar(TREE_CHAR, tree);

    Serial.begin(9600);
    pinMode(BUTTON_ENTER, INPUT);
    pinMode(BUTTON_SELECT, INPUT);

    unsigned char i = 0;
    tasks[i].state = INIT;
    tasks[i].period = 50;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &SM1_Tick;
    i++;
    delay_gcd = 1; // GCD
}


void loop() {
    for (unsigned char i = 0; i < tasksNum; ++i) {
        if ((millis() - tasks[i].elapsedTime) >= tasks[i].period) {
            tasks[i].state = tasks[i].TickFct(tasks[i].state);
            tasks[i].elapsedTime = millis(); // Last time this task was ran
        }
    }
}

void show_menu() {
    String menu[MENU_SIZE] = { "START", "SCORE" };

    for (int i = 0; i < MENU_SIZE; i++) {
        if (i == currentIndexMenu) {
            lcd.setCursor(0, i);
            lcd.print("-> ");
        }

        lcd.setCursor(3, i);
        lcd.print(menu[i]);
    }

    if (select) {
        currentIndexMenu = currentIndexMenu == 0 ? 1 : 0;
    }

    if (enter) {
        // currentIndexMenu == 0 ? startGame() : showScore();
    }
}