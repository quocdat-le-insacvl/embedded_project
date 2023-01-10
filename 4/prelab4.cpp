const unsigned long period = 1000;
unsigned long lastRan;
const int b_size = 7;
const int b[b_size] = {2, 3, 4, 5, 9, 10, 11};

void setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    Serial.begin(9600);
    lastRan = 0;
}

enum States {
    INIT, S0, S1
} state = INIT;

void Tick() {
    switch (state) {
        case INIT:
            state = S0;
            break;
        case S0:
            state = S1;
            break;
        case S1:
            state = S0;
            break;
        default: // should never get here
            break;
    }
    switch (state) {
        case INIT:
            break;
        case S0:
            for (int i = 0; i < 4; i++) {
                digitalWrite(b[i], LOW);
            }
            break;
        case S1:
            for (int i = 0; i < 4; i++) {
                digitalWrite(b[i], HIGH);
            }
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