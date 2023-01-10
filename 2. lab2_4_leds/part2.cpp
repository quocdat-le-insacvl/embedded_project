/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 2 Exercise 2
 * Exercise Description: [optional - include for your own benefit]
 **
 I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 **
 Demo Link: <URL>
*/

int B[4] = {2, 3, 4, 5};
int PD = 6;
int PU = 7;


int SPEED[3] = {250, 750, 1250};
int CURRENT_STATE = 0; // 0 1 2
int CURRENT_SEQUENCE = 240;
int INCREMENT = 1;
int PD_x_state;
int PU_y_state;
int LEDs_STATE = 0; // turn off by default

void setup() {
    pinMode(PD, INPUT);
    pinMode(PU, INPUT_PULLUP);

    for (int i = 0; i < 4; i++) {
        pinMode(B[i], OUTPUT);
    }
    Serial.begin(9600);
}

void leds_update() {
    for (int i = 0; i < 4; i++) {
        int k_th = 3 - i;
        int status = (CURRENT_SEQUENCE & (1 << k_th)) >> k_th;
        digitalWrite(B[i], status);
//        Serial.print(status);
    }
//    Serial.println();
}

void next_sequence() {
    int k = CURRENT_SEQUENCE;
    int inc = INCREMENT;
    // update increment
    if (k == 15 || k == 0 || k == 240) {
        inc *= -1;
    }
    // update the sequence k
    if (inc == 1) {
        k = k << 1;
    } else {
        k = k >> 1;
    }
    CURRENT_SEQUENCE = k;
    INCREMENT = inc;
}

void update_tempo() {
    // get states of button
    PD_x_state = digitalRead(PD);
    PU_y_state = digitalRead(PU);

    if (PD_x_state == HIGH) {
        // decrease tempo
        if (CURRENT_STATE > 0) CURRENT_STATE--;
    }

    if (PU_y_state == LOW) {
        // increase tempo
        if (CURRENT_STATE < 2) CURRENT_STATE++;
    }
}

void loop() {
    update_tempo();

    next_sequence();

    leds_update();

    Serial.println(CURRENT_STATE);

    delay(SPEED[CURRENT_STATE]);

}