/* Your Name : Yu Lai
 * E-mail: ylai048@ucr.edu
 * Discussion Section: 021
 * Assignment: Lab 7 Exercise
 * Exercise Description: The "Switch" of my Joystick is broken.
 *                       I had to use another button to replace it by setting
 *                       pinMode(JS_BTN, INPUT_PULLUP);
 *                       Please check the video to see the modified circuit for more detail.
 **
 I acknowledge all content contained herein, excluding
 * template or example code, is my own original work.
 **
 Demo Link: <URL>
*/
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT11
#define PRLN(x) Serial.println(x)
#define PR(x) Serial.print(x); Serial.print(" ")
DHT dht(DHTPIN, DHTTYPE);
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Temp, STemp = 75, Hum, SHum = 30;

//struct {
//    x = A0;
//};

int JS_X = A1;
int JS_Y = A2;
int JS_BTN = 12;
int JS_THRESHOLD = 250;


typedef struct task {
    int state;
    unsigned long period;
    unsigned long elapsedTime;

    int (*TickFct)(int);
} task;


int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];


void display_lcd() {
    //    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(Temp);
    lcd.print(" ");
    lcd.print("STemp:");
    lcd.print(STemp);
    lcd.setCursor(0, 1);
    lcd.print("Hum:");
    lcd.print(Hum);
    lcd.print(" ");
    lcd.print("SHum:");
    lcd.print(SHum);
    //    delay(1000);
}


enum LED_COLOR {
    BLUE = 0,
    YELLOW = 1,
    WHITE = 2,
    RED = 3,
};

int duty[4] = { 20, 20, 60, 95 };
//int color_pin[4] = {BLUE, YELLOW, WHITE, RED};
int color_pin[4] = { 8, 9, 10, 11 };
int period[4] = { 200, 400, 300, 100 };
int current[4] = { 0, 0, 0, 0 };
int cache[4] = { 0, 0, 0, 0 };
int start[4] = { 0, 0, 0, 0 };
int is_on[4] = { 0, 0, 0, 0 };

//typedef struct IndoorPlant {
//    int current = 0;
//    int is_on = 1;
//    int pause_duration = 0;
//    unsigned long cache = 0;
//    unsigned long start = 0;
//    int timer[3] = {3, 5, 2};
//    int period[3] = {300, 500, 100};
//    int duty[3] = {20, 70, 10};
//    int color[4] = {BLUE, YELLOW, WHITE, RED};
//} IndoorPlant;
//
//struct IndoorPlant indoor_plant;

void leds_on(int k) {
    digitalWrite(color_pin[k], 1);
}

void leds_reset() {
    digitalWrite(color_pin[YELLOW], 0);
    digitalWrite(color_pin[BLUE], 0);
    digitalWrite(color_pin[RED], 0);
    digitalWrite(color_pin[WHITE], 0);
}

void leds_update_with_duty(int cur) {
    // on / off : using cache and period
    int cur_duty = duty[cur];
    cur_duty = is_on[cur] ? cur_duty : 100 - cur_duty;
    unsigned long mul = period[cur];
    mul *= cur_duty;
    mul /= 100;
    if (millis() - cache[cur] >= mul) {
        cache[cur] = millis();
        is_on[cur] = !is_on[cur];
    }
    digitalWrite(color_pin[cur], is_on[cur]);
}

enum IndoorPlant {
    SM1_INIT, SM1_ON, SM1_OFF
};

void log() {
    Serial.println("HI!");
}

void log2() {
    Serial.println("HI!2");
}

int running = 1;

int IndoorPlant_Tick(int state1) {
    switch (state1) { // State transitions
    case SM1_INIT:
        state1 = SM1_ON;
        break;

    case SM1_ON:
        if (!running)
            state1 = SM1_OFF;
        break;

    case SM1_OFF:
        if (running)
            state1 = SM1_ON;
        break;
    }

    switch (state1) { // State Action
    case SM1_INIT:
        break;

    case SM1_ON:
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        float f = dht.readTemperature(true);
        if (isnan(h) || isnan(t) || isnan(f)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }
        float hif = dht.computeHeatIndex(f, h);
        float hic = dht.computeHeatIndex(t, h, false);
        Hum = h;
        Temp = f;
        break;

    case SM1_OFF:
        leds_reset();
        break;
    }
    return state1;
}

enum JS_Status {
    OFF, PRESSED, JS_DOWN, JS_UP, JS_RIGHT, JS_LEFT
} JS;

int LAST_SAMPLE;
int LAST_JS;

void js_update() {
    if (millis() - LAST_SAMPLE < 300) {
        JS = OFF;
        return;
    }
    int j_x = analogRead(JS_X);
    int j_y = analogRead(JS_Y);
    int j_btn = digitalRead(JS_BTN);
    JS = OFF;
    if (!j_btn) {
        JS = PRESSED;
    }
    if (j_x <= JS_THRESHOLD) {
        JS = JS_UP;
    }
    if (j_x >= 1000 - JS_THRESHOLD) {
        JS = JS_DOWN;
    }
    if (j_y <= JS_THRESHOLD) {
        JS = JS_LEFT;
    }
    if (j_y >= 1000 - JS_THRESHOLD) {
        JS = JS_RIGHT;
    }
    LAST_JS = JS;
    LAST_SAMPLE = millis();
    //    PR(j_x);
    //    PR(j_y);
    //    PR(j_btn);
    //    PRLN(JS);
    //    PRLN(" ");
}

enum Controller {
    SM2_INIT, on, off
};

int is_setting_temp = 1;

int Controller_Tick(int state1) {
    js_update();
    switch (state1) { // State transitions
    case SM2_INIT:
        state1 = off;
        break;

    case on:
        if (JS == PRESSED) {
            state1 = off;
            running = 0;
        }
        break;

    case off:
        if (JS == PRESSED) {
            state1 = on;
            running = 1;
        }
        break;
    }

    switch (state1) { // State Action
    case SM2_INIT:
        break;

    case on:
        //            leds_reset();
        switch (JS) {
        case PRESSED:
            break;

        case JS_DOWN:
            is_setting_temp = 0;
            break;

        case JS_UP:
            is_setting_temp = 1;
            break;

        case JS_RIGHT:
            if (is_setting_temp)
                STemp++;
            else SHum++;
            break;

        case JS_LEFT:
            if (is_setting_temp)
                STemp--;
            else SHum--;
            break;

        }
        leds_reset();
        if (STemp > Temp) {
            leds_update_with_duty(RED);
        } else if (STemp < Temp) {
            leds_update_with_duty(WHITE);
        }
        if (SHum > Hum) {
            leds_update_with_duty(BLUE);
        } else if (SHum < Hum) {
            leds_update_with_duty(YELLOW);
        }
        display_lcd();

        //            Serial.println(JS);
        break;

    case off:
        lcd.clear();
        leds_reset();
        break;
    }
    return state1;
}


void setup() {
    pinMode(color_pin[YELLOW], OUTPUT);
    pinMode(color_pin[RED], OUTPUT);
    pinMode(color_pin[BLUE], OUTPUT);
    pinMode(color_pin[WHITE], OUTPUT);
    //    pinMode(JS_X, INPUT);
    //    pinMode(JS_X, INPUT);
    pinMode(JS_BTN, INPUT_PULLUP);

    Serial.begin(9600);
    unsigned char i = 0;
    tasks[i].state = SM1_INIT;
    tasks[i].period = 500;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &IndoorPlant_Tick;
    i++;
    tasks[i].state = SM2_INIT;
    tasks[i].period = 100;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &Controller_Tick;
    delay_gcd = 100; // GCD
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    Serial.begin(9600);
    dht.begin();

}

void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):

    for (unsigned char i = 0; i < tasksNum; ++i) {
        if ((millis() - tasks[i].elapsedTime) >= tasks[i].period) {
            tasks[i].state = tasks[i].TickFct(tasks[i].state);
            tasks[i].elapsedTime = millis(); // Last time this task was ran
        }
    }
}