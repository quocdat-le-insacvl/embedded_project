/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 5 Exercise 2
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
int WRONG_SHOW = -1;
unsigned long last_blink;
int rotate_var;
int led_var;
int ROTATE_STEP;
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

int passwd[4] = {JS_UP, JS_UP, JS_LEFT, JS_RIGHT};

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
}

typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;

    int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 3;
task tasks[tasksNum];

void rotate_flag() {
    for (int k = 0; k < 4; k++) {
        digitalWrite(sig[k], steps[i][k]);
    }
}

void log(char *str) {
    Serial.println(str);
}

enum LOCK_States {
    LOCK_INIT, LOCKED, UNLOCKED, CHANGING_PASSWD,
};

int TYPING = 0;
int user_input[4];
int cache = OFF;
unsigned long last_type;

int is_correct() {
    int ans = 1;
    for (int k = 0; k < 4; k++) {
        ans &= (user_input[k] == passwd[k]);
    }
    return ans;
}

void display_code() {
    Serial.print("USER : ");
    for (int k = 0; k < 4; k++) {
        Serial.print(user_input[k]);
        Serial.print(" ");
    }
    Serial.println();
    Serial.print("REAL CODE : ");
    for (int k = 0; k < 4; k++) {
        Serial.print(passwd[k]);
        Serial.print(" ");
    }
    Serial.println();
}

int LOCK_Tick(int state0) {
    js_update();

    switch (state0) { // State transitions
        case LOCK_INIT:
            state0 = LOCKED;
            break;

        case LOCKED:
            if (JS != OFF && JS != PRESSED) {
                cache = JS;
            } else {
                if (cache != OFF) {
                    user_input[TYPING++] = cache;
                    cache = OFF;
                    Serial.print("TYPED : ");
                    Serial.println(user_input[TYPING - 1]);
                }
            }
            if (TYPING == 4) {
                display_code();
                TYPING = 0;
                // check if correct
                if (is_correct()) {
                    Serial.println("CORRECT");
                    state0 = UNLOCKED;
                    led_var = 1; // all
                    rotate_var = 1; // open
                } else {
                    Serial.println("INCORRECT");
                    led_var = 2;
                }
            }
            break;

        case UNLOCKED:
            if (JS != OFF && JS != PRESSED) {
                cache = JS;
            } else {
                if (cache != OFF) {
                    user_input[TYPING++] = cache;
                    cache = OFF;
                    Serial.print("TYPED : ");
                    Serial.println(user_input[TYPING - 1]);
                }
            }
            if (JS == PRESSED) {
                led_var = 3;
                state0 = CHANGING_PASSWD;
            }
            if (TYPING == 4) {
                display_code();
                TYPING = 0;
                // check if correct
                if (is_correct()) {
                    Serial.println("CORRECT");
                    state0 = LOCKED;
                    rotate_var = 2; // close
                } else {
                    Serial.println("INCORRECT");
//                    led_var = 2;
                }
            }
            break;

        case CHANGING_PASSWD:
            if (JS != OFF && JS != PRESSED) {
                cache = JS;
            } else {
                if (cache != OFF) {
                    passwd[TYPING++] = cache;
                    cache = OFF;
                }
            }
            if (TYPING == 4) {
                TYPING = 0;
                // check if correct
                Serial.println("PASSWORD UPDATED !");
                state0 = UNLOCKED;
                led_var = 1;
            }
            break;
    }

    switch (state0) { // State Action
        case LOCK_INIT:
            break;

        case LOCKED:
            break;

        case UNLOCKED:
            break;
    }
    return state0;
}


enum ROTATE_States {
    ROTATE_INIT, CLOCKWISE, COUNTER_CLOCKWISE, ROTATE_STOPPING
};

int ROTATE_Tick(int state1) {
    js_update();

    switch (state1) { // State transitions
        case ROTATE_INIT:
//            state1 = COUNTER_CLOCKWISE;
//            state1 = CLOCKWISE;
//            rotate_var = 1;
            state1 = ROTATE_STOPPING;
            break;

        case COUNTER_CLOCKWISE:
            if (ROTATE_STEP == 0) {
                state1 = ROTATE_STOPPING;
            }
            break;

        case CLOCKWISE:
            if (ROTATE_STEP == 0) {
                state1 = ROTATE_STOPPING;
                led_var = 3; // default
            }
            break;

        case ROTATE_STOPPING:
            if (rotate_var == 1) {
                state1 = COUNTER_CLOCKWISE;
            } else if (rotate_var == 2) {
                state1 = CLOCKWISE;
            }
            rotate_var = 0;
            ROTATE_STEP = 256 * 8; // 256 steps * 8 states
            break;

    }
    switch (state1) { // State Action
        case ROTATE_INIT:
            break;

        case COUNTER_CLOCKWISE:
            if (ROTATE_STEP > 0) {
                ROTATE_STEP--;
                i--;
                if (i == -1) {
                    i = 7;
                }
                rotate_flag();
                rotating_clockwise = 0;
            }
            break;

        case CLOCKWISE:
            if (ROTATE_STEP > 0) {
                ROTATE_STEP--;
                i++;
                if (i == 8) {
                    i = 0;
                }
                rotate_flag();
                rotating_clockwise = 1;
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
    LEDs_DEFAULT, LEDs_PRESSED, LEDs_UP, LEDs_DOWN, LEDs_RIGHT, LEDs_LEFT, LEDs_INIT, LEDs_WRONG, LEDs_ALL,
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
//            state2 = LEDs_RIGHT;
//            WRONG_SHOW = 6;
//            state2 = LEDs_WRONG;
//            state2 = LEDs_ALL;
            state2 = LEDs_DEFAULT;
            break;

        case LEDs_ALL:
//            state2 = JS;
            if (led_var == 3) {
                led_var = 0;
                state2 = LEDs_DEFAULT;
            }
            break;

        case LEDs_DEFAULT:
            leds_reset();
            state2 = JS;
            if (led_var == 1) {
                led_var = 0;
                state2 = LEDs_ALL;
            } else if (led_var == 2) {
                led_var = 0;
                state2 = LEDs_WRONG;
                WRONG_SHOW = 6;
            }
            break;

        case LEDs_WRONG:
            if (WRONG_SHOW == -1) {
                state2 = LEDs_DEFAULT;
            }
            break;

        default: // I don't want to repeat this for all task
            leds_reset();
            state2 = JS;
            break;
    }

    switch (state2) { // State Action
        case LEDs_INIT:
            break;

        case LEDs_WRONG:
            if (WRONG_SHOW >= 0) {
                if (millis() - last_blink > 200) {
                    if (WRONG_SHOW & 1) {
                        leds_on();
                    } else {
                        leds_reset();
                    }
                    WRONG_SHOW--;
                    last_blink = millis();
                }
            }
            break;

        case LEDs_ALL:
            leds_on();
            break;

        case LEDs_PRESSED:
//            leds_on();
            break;

        case LEDs_DEFAULT:
            break;

        case LEDs_UP:
            digitalWrite(UP, 1);
            break;

        case LEDs_DOWN:
            leds_reset();
            digitalWrite(DOWN, 1);
            break;

        case LEDs_RIGHT:
            leds_reset();
            digitalWrite(RIGHT, 1);
            break;

        case LEDs_LEFT:
            leds_reset();
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
//    pinMode(JS_X, INPUT);
//    pinMode(JS_X, INPUT);
    pinMode(JS_BTN, INPUT_PULLUP);
    Serial.begin(9600);


    unsigned char j = 0;
    tasks[j].state = LOCK_INIT;
    tasks[j].period = 1;
    tasks[j].elapsedTime = 0;
    tasks[j].TickFct = &LOCK_Tick;
    j++;
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