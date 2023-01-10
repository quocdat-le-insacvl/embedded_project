/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 4 Exercise 1
 * Exercise Description: [optional - include for your own benefit]
 **
 I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 **
 Demo Link: <URL>
*/


const unsigned long period = 1000;
unsigned long lastRan;
int LEDs[4] = {2, 3, 4 ,5};
int RBG[3] = {9, 10, 11};
int POS = 0;

void setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    for (int i = 0; i < 3; i++) {
        pinMode(RBG[i], OUTPUT);
    }
    Serial.begin(9600);
    lastRan = 0;
}

int read_potentiometer() {
    int A0_int = analogRead(A0);
    int translation = map(A0_int, 0, 1023, 100, 500);
    return translation;
}

void leds_light_up() {
    for (int i = 0; i < 4; i++) {
        int status = i == POS ? 1 : 0;
        digitalWrite(LEDs[i], status);
    }
}

void leds_reset() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(LEDs[i], 0);
    }
}

//void leds_update() {
//    leds_reset();
//    // update status
//    int k = read_potentiometer();
//    for (int i = 0; i < k; i++) {
//        LEDs_STATUS[i] = 1;
//    }
//    leds_light_up();
//}

enum States {
    INIT, LEFT, RIGHT
} state = INIT;

void Tick() {
    switch (state) {
        case INIT:
            state = LEFT;
            break;
        case LEFT:
            if (POS == 3) {
                state = RIGHT;
            }
            break;
        case RIGHT:
            if (POS == 0) {
                state = LEFT;
            }
            break;
        default: // should never get here
            break;
    }
    switch (state) {
        case INIT:
            break;
        case LEFT:
            leds_light_up();
            POS++;
            break;
        case RIGHT:
            leds_light_up();
            POS--;
            break;
        default: // should never get here
            break;
    }
}

void loop() {
    if ((millis() - lastRan) > period) {
        Tick();
        lastRan = millis();
    }
}
