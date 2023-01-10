/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 3 Exercise 2
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
int LIGHT_THRESHOLD = 70;
int TMP[3] = {0, 0, 0};

void setup() {
    // RGB
    for (int i = 0; i < 4; i++) {
        pinMode(RBG[i], OUTPUT);
    }

    // red LEDs
    for (int i = 0; i < 4; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    Serial.begin(9600);
}

int read_potentiometer() {
    int A0_int = analogRead(A0);
    int translation = map(A0_int, 0, 1023, 0, 5);
    Serial.print(A0_int);
    Serial.print("   ");
    Serial.println(translation);
    return translation;
}

// return 0 = Dark, 1 = LIGHT
int read_photoresistor() {
    int A1_int = analogRead(A1);
    Serial.print("----------- ");
    Serial.println(A1_int);
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

void rgb_update(int color) {
    TMP[color]++;
    float angle = radians(TMP[color]);
    int MAX_BRIGHTNESS = 50; // I prefer 200 but default -> 255;
    float brightness = (MAX_BRIGHTNESS / 2) + (MAX_BRIGHTNESS / 2) * sin(angle);
    VAL_RBG[color] = (int) brightness;

    for (int i = 0; i < 3; i++) {
        analogWrite(RBG[i], VAL_RBG[i]);
    }
}

enum States {
    INIT, RED, GREEN, BLUE
} state = INIT;

// This function takes in the state as an argument & returns the current state
void Tick() {

    switch (state) { // State transitions

        case INIT:
            //State Transition
            state = RED;
            break;

        case RED:
            state = ((millis() % 500 == 0)) ? GREEN : RED;
            break;

        case GREEN:
            state = ((millis() % 500 == 0)) ? BLUE : GREEN;
            break;

        case BLUE:
            state = ((millis() % 500 == 0)) ? RED : BLUE;
            break;
    }

    switch (state) { // State Action

        case INIT:
            //State Action
            break;

        case RED:
            if (millis() % 30 == 0)
                rgb_update(0);
            break;

        case GREEN:
            if (millis() % 30 == 0)
            rgb_update(1);
            break;

        case BLUE:
            if (millis() % 30 == 0)
            rgb_update(2);
            break;
    }
}

void loop() {

    ///Default arduino function
//    int A1_int = analogRead(A1);
//    Serial.println(analogRead(A1_int));
    Tick();
}