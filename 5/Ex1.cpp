/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 5 Exercise 1
 * Exercise Description: [optional - include for your own benefit]
 **
 I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 **
 Demo Link: <URL>
*/
unsigned long last_rotate;
int i = 0;
int c = 0;
int rotating_clockwise = 0;
int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
int UP = 3;
int DOWN = 4;
int LEFT = 2;
int RIGHT = 5;
int JS_X = A0;
int JS_Y = A1;
int JS_BTN = 7;
int JS_THRESHOLD = 200;
int MIN_SPEED = 500;
int ROTATE_SPEED = 1; // 1 -> 500 : fastest to slowest, then we will use map : [1:500] -> [1:5] for example
int sig[4] = {IN1,
              IN2,
              IN3,
              IN4};
int steps[8][4]{ //codes for the motor to turn properly
        {0, 0, 0, 1},
        {0, 0, 1, 1},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
};

enum JS_Status {
    OFF, PRESSED, JS_UP, JS_DOWN, JS_RIGHT, JS_LEFT
} JS;

void js_update() {
    int j_x = analogRead(JS_X);
    int j_y = analogRead(JS_Y);
    int j_btn = digitalRead(JS_BTN);
    JS = OFF;
    if (!j_btn) {
        JS = PRESSED;
    }
    if (j_x <= JS_THRESHOLD) {
        JS = JS_DOWN;
    }
    if (j_x >= 1000 - JS_THRESHOLD) {
        JS = JS_UP;
    }
    if (j_y <= JS_THRESHOLD) {
        JS = JS_LEFT;
    }
    if (j_y >= 1000 - JS_THRESHOLD) {
        JS = JS_RIGHT;
    }
//    Serial.print("X: ");
//    Serial.print(j_x);
//    Serial.print(" Y: ");
//    Serial.print(j_y);
//    Serial.print(" BTN: ");
//    Serial.print(j_btn);
//    Serial.print(" JS: ");
//    Serial.println(JS);
}

typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;

    int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

void rotate_flag() {
    for (int k = 0; k < 4; k++) {
        digitalWrite(sig[k], steps[i][k]);
    }
}

enum ROTATE_States {
    ROTATE_INIT, CLOCKWISE, COUNTER_CLOCKWISE, ROTATE_STOPPING
};

void log(char *str) {
    Serial.println(str);
}

int ROTATE_Tick(int state1) {
    js_update();

    switch (state1) { // State transitions
        case ROTATE_INIT:
            state1 = COUNTER_CLOCKWISE;
            break;

        case COUNTER_CLOCKWISE:
            if (JS == JS_LEFT) state1 = CLOCKWISE;
            else if (JS == JS_UP) {
                ROTATE_SPEED--;
                ROTATE_SPEED = max(1, ROTATE_SPEED);
            } else if (JS == JS_DOWN) {
                ROTATE_SPEED++;
                ROTATE_SPEED = min(MIN_SPEED, ROTATE_SPEED);
            } else if (JS == PRESSED){
                state1 = ROTATE_STOPPING;
            }
//            Serial.print(" JS: ");
//            Serial.println(JS);
            break;

        case CLOCKWISE:
            if (JS == JS_RIGHT) state1 = COUNTER_CLOCKWISE;
            else if (JS == JS_UP) {
                ROTATE_SPEED--;
                ROTATE_SPEED = max(1, ROTATE_SPEED);
            } else if (JS == JS_DOWN) {
                ROTATE_SPEED++;
                ROTATE_SPEED = min(MIN_SPEED, ROTATE_SPEED);
            } else if (JS == PRESSED){
                state1 = ROTATE_STOPPING;
            }
            break;

        case ROTATE_STOPPING:
            if (JS != PRESSED) {
                state1 = (rotating_clockwise) ? CLOCKWISE : COUNTER_CLOCKWISE;
            }
            break;

    }
    int speed = map(ROTATE_SPEED, 1, 501, 1, 40);
//    int speed = ROTATE_SPEED;
    switch (state1) { // State Action
        case ROTATE_INIT:
            break;

        case COUNTER_CLOCKWISE:
//            log("HI");
            if (millis() - last_rotate > speed) {
                i--;
                if (i == -1) {
                    i = 7;
                }
                rotate_flag();
                rotating_clockwise = 0;
                last_rotate = millis();
            }
            break;

        case CLOCKWISE:
            if (millis() - last_rotate > speed) {
                i++;
                if (i == 8) {
                    i = 0;
                }
                rotate_flag();
                rotating_clockwise = 1;
                last_rotate = millis();
            }
            break;

        case ROTATE_STOPPING:
//            rotate_flag();
            break;
    }
//    Serial.println(ma);

    return state1;
}

enum LEDs_States {
    LEDs_DEFAULT, LEDs_PRESSED, LEDs_UP, LEDs_DOWN, LEDs_RIGHT, LEDs_LEFT, LEDs_INIT,
};

void leds_reset() {
    digitalWrite(UP, 0);
    digitalWrite(DOWN, 0);
    digitalWrite(RIGHT, 0);
    digitalWrite(LEFT, 0);
}

void leds_on() {
    digitalWrite(UP, 1);
    digitalWrite(DOWN, 1);
    digitalWrite(RIGHT, 1);
    digitalWrite(LEFT, 1);
}

int LEDs_Tick(int state2) {
    js_update();
    switch (state2) { // State transitions
        case LEDs_INIT:
            //State Transition
            state2 = LEDs_RIGHT;
            break;

        default: // I don't want to repeat this for all task
            state2 = JS;
            break;
    }
    leds_reset();
    switch (state2) { // State Action
        case LEDs_INIT:
            break;

        case LEDs_PRESSED:
            leds_on();
            break;

        case LEDs_DEFAULT:
            if (rotating_clockwise) {
                digitalWrite(2, 1);
            } else {
                digitalWrite(5, 1);
            }
            break;

        case LEDs_UP:
            digitalWrite(UP, 1);
            break;

        case LEDs_DOWN:
            digitalWrite(DOWN, 1);
            break;

        case LEDs_RIGHT:
            digitalWrite(RIGHT, 1);
            break;

        case LEDs_LEFT:
            digitalWrite(LEFT, 1);
            break;
//            int j_x = analogRead(JS_X);
//            int j_y = analogRead(JS_Y);
//            int j_btn = digitalRead(JS_BTN);
//
//            Serial.print("X: "); Serial.print(j_x);
//            Serial.print(" Y: " ); Serial.print(j_y);
//            Serial.print(" BTN: "); Serial.println(j_btn);

    }

    return state2;
}

void setup() {
    // put your setup code here, to run once:
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(UP, OUTPUT);
    pinMode(DOWN, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(RIGHT, OUTPUT);
    pinMode(JS_BTN, INPUT_PULLUP);
    Serial.begin(9600);


    unsigned char j = 0;
    tasks[j].state = ROTATE_INIT;
    tasks[j].period = 1;
    tasks[j].elapsedTime = 0;
    tasks[j].TickFct = &ROTATE_Tick;
    j++;
    tasks[j].state = LEDs_INIT;
    tasks[j].period = 50;
    tasks[j].elapsedTime = 0;
    tasks[j].TickFct = &LEDs_Tick;

    delay_gcd = 1; // GCD
}

void loop() {
    unsigned char i;
    for (i = 0; i < tasksNum; ++i) {
        if ((millis() - tasks[i].elapsedTime) >= tasks[i].period) {
            tasks[i].state = tasks[i].TickFct(tasks[i].state);
            tasks[i].elapsedTime = millis(); // Last time this task was ran
        }
    }
}