/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 3 Exercise 3
 * Exercise Description: [optional - include for your own benefit]
 **
 I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 **
 Demo Link: <URL>
*/
int LEDs[4] = {5, 4, 3, 2};
int LEDs_STATUS[4] = {0, 0, 0, 0};
int RBG[3] = {9, 10, 11};
int VAL_RBG[3] = {0, 0, 0};
int LIGHT_THRESHOLD = 80;
int TMP = 0;

void setup() {
    // RGB
    for (int i = 0; i < 4; i++) {
        pinMode(RBG[i], OUTPUT);
    }
    for (int i = 0; i < 4; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    Serial.begin(9600);
}

void rgb_update() {
    TMP++;
    float angle = radians(TMP);
    int MAX_BRIGHTNESS = 50; // I prefer 50 but default -> 255;
    for (int i = 0; i < 3; i++) {
        float brightness = (MAX_BRIGHTNESS / 2) + (MAX_BRIGHTNESS / 2) * sin(angle + i * 120);
        VAL_RBG[i] = (int) brightness;
    }

    for (int i = 0; i < 3; i++) {
        analogWrite(RBG[i], VAL_RBG[i]);
    }
}

void rgb_off() {
    for (int i = 0; i < 3; i++) {
        analogWrite(RBG[i], 0);
    }
}

int read_potentiometer() {
    int A0_int = analogRead(A0);
    int translation = map(A0_int, 0, 1023, 0, 5);
    return translation;
}

// return 0 = Dark, 1 = LIGHT
int read_photoresistor() {
    int A1_int = analogRead(A1);
//    Serial.println(A1_int);
    return A1_int > LIGHT_THRESHOLD ? 1 : 0;
}

void leds_light_up() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(LEDs[i], LEDs_STATUS[i]);
    }
}

void leds_reset() {
    for (int i = 0; i < 4; i++) {
        LEDs_STATUS[i] = 0;
    }
}

void leds_update() {
    leds_reset();
    // update status
    int k = read_potentiometer();
    for (int i = 0; i < k; i++) {
        LEDs_STATUS[i] = 1;
    }
    leds_light_up();
}

enum States {
    INIT, BRIGHT, DARK
} state = INIT;

// This function takes in the state as an argument & returns the current state
void Tick() {

    switch (state) { // State transitions

        case INIT:
            //State Transition
            state = DARK;
            break;

        case DARK:
            if (read_photoresistor()) {
                state = BRIGHT;
            }
            break;

        case BRIGHT:
            if (!read_photoresistor()) {
                state = DARK;
            }
            break;
    }

    switch (state) { // State Action

        case INIT:
            //State Action
            break;

        case DARK:
            leds_reset();
            leds_light_up();
            if (millis() % 2 == 0)
                rgb_update();
            break;

        case BRIGHT:
            leds_update();
            rgb_off();
            break;
    }
}

void loop() {

    ///Default arduino function
    Tick();
}