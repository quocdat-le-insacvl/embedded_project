/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 2 Exercise 1
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

void setup() {
    pinMode(PD, INPUT);
    pinMode(PU, INPUT_PULLUP);

    for (int i = 0; i < 4; i++) {
        pinMode(B[i], OUTPUT);
    }
    Serial.begin(9600);
}

void leds_update(int status) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(B[i], status);
    }
}

int PD_x_state;
int PU_y_state;
int LEDs_STATE = 0; // turn off by default

void loop() {
    // get states of button
    PD_x_state = digitalRead(PD);
    PU_y_state = digitalRead(PU);

    // Serial.println(PD_x_state);// Press = HIGH, default = LOW
//    Serial.println(PU_y_state); // Press = LOW, default = HIGH
    if (PU_y_state == LOW) {
        LEDs_STATE = 1;
    }

    if (PD_x_state == HIGH) {
        LEDs_STATE = 0;
    }

    leds_update(LEDs_STATE);

}