/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 6 Exercise 1
 * Exercise Description: [optional - include for your own benefit]
 **
 I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 **
 Demo Link: <URL>
*/
int LIGHT_THRESHOLD = 30;
enum LED_COLOR {
    YELLOW = 2,
    BLUE = 3,
    RED = 4,
    WHITE = 5,
    GREEN = 6,
};

typedef struct IceMaker {
    int current = 0;
    int is_on = 1;
    int pause_duration = 0;
    unsigned long cache = 0;
    unsigned long start = 0;
    int timer[3] = {3, 5, 2};
    int period[3] = {300, 500, 100};
    int duty[3] = {20, 70, 10};
    int color[3] = {BLUE, WHITE, GREEN};
} IceMaker;
struct IceMaker ice_maker;

typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;

    int (*TickFct)(int);
} task;


int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

int SWITCH_STATE = 0;
unsigned long water_last_sampling = -50;
unsigned long ice_last_sampling = -50;
int CACHE_WATER = 100;
int CACHE_ICE = 100;

int read_water_sensor() {
    if (millis() - water_last_sampling >= 50) {
        CACHE_WATER = analogRead(A0);
        water_last_sampling = millis();
    }
    return CACHE_WATER;
}

int read_ice_sensor() {
    if (millis() - ice_last_sampling >= 200) {
        CACHE_ICE = analogRead(A1);
        ice_last_sampling = millis();
    }
    return CACHE_ICE;
}

int ice_sensor_is_off() {
    return read_ice_sensor() < LIGHT_THRESHOLD;
}

int water_sensor_is_off() {
    return read_water_sensor() < LIGHT_THRESHOLD;
}

void led_on(int k) {
    digitalWrite(k, 1);
}

void led_off(int k) {
    digitalWrite(k, 0);
}

void leds_reset() {
    digitalWrite(YELLOW, 0);
//    digitalWrite(BLUE, 0);
    digitalWrite(RED, 0);
//    digitalWrite(WHITE, 0);
//    digitalWrite(GREEN, 0);
}

void leds_reset_all() {
    digitalWrite(YELLOW, 0);
    digitalWrite(BLUE, 0);
    digitalWrite(RED, 0);
    digitalWrite(WHITE, 0);
    digitalWrite(GREEN, 0);
}

void leds_reset2() {
//    digitalWrite(YELLOW, 0);
    digitalWrite(BLUE, 0);
//    digitalWrite(RED, 0);
    digitalWrite(WHITE, 0);
    digitalWrite(GREEN, 0);
}

enum SM1_States {
    SM1_INIT, on, off, pause,
};

unsigned STOP_MOMENT = 0;
int first_time = 1;
int STOP_FLAG = 1;

int SM1_Tick(int state1) {
//    Serial.print(" SWITCH: ");
//    Serial.print(SWITCH_STATE);
//    Serial.print(" STATE1:");
//    Serial.print(state1);
////
//    Serial.print(" WATER:");
//    Serial.print(read_water_sensor());
//    Serial.print(" ICE:");
//    Serial.println(read_ice_sensor());
    int is_off;
    switch (state1) { // State transitions
        case SM1_INIT:
            state1 = off;
            break;

        case on:
//            is_off = ice_sensor_is_off() && water_sensor_is_off();
//            if (SWITCH_STATE && !is_off) {
//                state1 = on;
//                SWITCH_STATE = 0;
//            }
            if (STOP_FLAG) {
                STOP_FLAG = 0;
                if (first_time) {
                    first_time = 0;
                } else {
                    ice_maker.pause_duration += millis() - STOP_MOMENT;
                }
            }
            if (ice_sensor_is_off() || water_sensor_is_off()) {
                state1 = pause;
                STOP_MOMENT = millis();
            }
            if (ice_sensor_is_off() && water_sensor_is_off()) {
                state1 = off;
                STOP_MOMENT = millis();
                SWITCH_STATE = -1;
            }
            break;

        case off:
            STOP_FLAG = 1;
            is_off = ice_sensor_is_off() && water_sensor_is_off();
            if (!is_off && SWITCH_STATE != 1) {
                SWITCH_STATE = 0;
            }
            if (SWITCH_STATE && !is_off) {
                state1 = on;
                SWITCH_STATE = 0;
            }
            if (is_off && SWITCH_STATE == 0) {
                SWITCH_STATE = 1;
            }
            break;
    }

    switch (state1) {  // State transitions : I got an exceptional bug, and I had to split like this
        case pause:
            STOP_FLAG = 1;
            if (!ice_sensor_is_off() && !water_sensor_is_off()) {
                state1 = on;
            }
            if (ice_sensor_is_off() && water_sensor_is_off()) {
                SWITCH_STATE = -1;
                state1 = off;
            }
//            if (SWITCH_STATE && !is_off) {
//                state1 = on;
//                SWITCH_STATE = 0;
//            }
            break;
    }

    switch (state1) { // State Action
        case SM1_INIT:
            break;

        case on:
            leds_reset();
            break;

        case off:
            leds_reset_all();
            break;

        case pause:
            leds_reset_all();
            if (ice_sensor_is_off()) {
                led_on(YELLOW);
            }
            if (water_sensor_is_off()) {
                led_on(RED);
            }
            break;
    }
    return state1;
}

enum SM2_States {
    SM2_INIT, on2, off2,
};

void log() {
    Serial.print(" I : ");
    Serial.print(ice_maker.current);
    Serial.print(" Is On : ");
    Serial.print(ice_maker.is_on);
    Serial.print(" Start : ");
    Serial.print(ice_maker.start);
    Serial.print(" Cache: ");
    Serial.println(ice_maker.cache);
}
int first2 = 1;

int SM2_Tick(int state2) {
    switch (state2) { // State transitions
        case SM2_INIT:
            state2 = off2;
            break;
        case on2:
            if (STOP_FLAG) {
                state2 = off2;
            }
            break;

        case off2:
            if (!STOP_FLAG) {
                state2 = on2;
            }
            break;
    }
    leds_reset2();
    switch (state2) { // State Action
        case SM2_INIT:
            break;
        case on2:
//            Serial.print(" Pause: ");
//            Serial.println(ice_maker.pause_duration);
            if (first2) {
                first2 = 0;
                ice_maker.start = millis();
                ice_maker.cache = millis();
            }
            //when cache == period -> reset cache + change state
            if (millis() - ice_maker.pause_duration - ice_maker.start >= ice_maker.timer[ice_maker.current] * 1000) {
                if (ice_maker.current == 2) {
                    ice_maker.current = 0;
                } else
                    ice_maker.current++;
                ice_maker.start = millis();
                ice_maker.cache = millis();
                ice_maker.is_on = 1;
                ice_maker.pause_duration = 0;
            }
            int current_light = ice_maker.current;
            // on / off : using cache and period
            int current_duty = ice_maker.duty[current_light];
            current_duty = ice_maker.is_on ? current_duty : 100 - current_duty;
            unsigned long mul = ice_maker.period[current_light];
            mul *= current_duty;
            mul /= 100;
            if (millis() - ice_maker.cache >= mul) {
                ice_maker.cache = millis();
                ice_maker.is_on = !ice_maker.is_on;
//                log();
            }
            digitalWrite(ice_maker.color[current_light], ice_maker.is_on);
            break;

        case off2:
            break;
    }
    return state2;
}

void setup() {
    pinMode(YELLOW, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(WHITE, OUTPUT);
    Serial.begin(9600);
// put your setup code here, to run once:
    unsigned char i = 0;
    tasks[i].state = SM1_INIT;
    tasks[i].period = 50;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &SM1_Tick;
    i++;
    tasks[i].state = SM2_INIT;
    tasks[i].period = 1;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &SM2_Tick;
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