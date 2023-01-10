int B[4] = { 2, 3, 4, 5 };
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

void leds_update(int signal) {
    for (int i = 0; i < 4; i++) {
        int k_th = 3 - i;
        int status = (signal & (1 << k_th)) >> k_th;
        digitalWrite(B[i], status);
    }
}

void loop() {
    int A0_int = analogRead(A0);
    Serial.println(A0_int);
    int translation = map(A0_int, 0, 1023, 0, 15);
    Serial.println(translation);

    leds_update(translation);

    delay(200);
}