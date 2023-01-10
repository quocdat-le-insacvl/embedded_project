/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 4 Exercise 3
 * Exercise Description: [optional - include for your own benefit]
 **
 I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 **
 Demo Link: <URL>
*/


const unsigned long period = 50;
unsigned long lastRan;
unsigned long lastSample;
int LEDs[4] = {2, 3, 4, 5};
int RBG[3] = {9, 10, 11};
int POS = 0;
int POT_VALUE;
int PHO_VALUE;

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

void read_potentiometer() {
    int A0_int = analogRead(A0);
    int translation = map(A0_int, 0, 1023, 0, 766); // 765 = 255 * 3
    POT_VALUE = translation;
}

void read_photoresistor() {
    int A1_int = analogRead(A1);
    int translation = map(A1_int, 0, 250, 0, 5);
    Serial.println(A1_int);
    PHO_VALUE = translation;
}

void leds_light_up() {
    for (int i = 0; i < 4; i++) {
        int status = i < PHO_VALUE;
        digitalWrite(LEDs[i], status);
    }
}

void leds_depend_on_photoresistor() {
    for (int i = 0; i < 4; i++) {
        int status = i < PHO_VALUE;
        digitalWrite(LEDs[i], status);
    }
}

void rgb_depend_on_potentiometer() {
    int pot_value = POT_VALUE;
    for (int i = 0; i < 3; i++) {
        int intensity = min(pot_value, 255);
        intensity = max(0, intensity);
        pot_value -= 255;
        analogWrite(RBG[i], intensity);
    }
}

void leds_reset() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(LEDs[i], 0);
    }
}


enum States {
    INIT, SAMPLE, UPDATE_DISPLAY
} state = INIT;

void Tick() {
    switch (state) {
        case INIT:
            state = SAMPLE;
            break;
        case SAMPLE:
            state = UPDATE_DISPLAY;
            break;
        case UPDATE_DISPLAY:
            state = SAMPLE;
            break;
        default: // should never get here
            break;
    }
    switch (state) {
        case INIT:
            break;
        case SAMPLE:
            if (millis() - lastSample > 100) {
                read_photoresistor();
                read_potentiometer();
                lastSample = millis();
            }
            break;
        case UPDATE_DISPLAY:
            rgb_depend_on_potentiometer();
            leds_depend_on_photoresistor();
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
//Serial.println(A1_int);