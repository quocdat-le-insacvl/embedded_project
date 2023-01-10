// shift register library
#include <SevSegShift.h>
#include <stdio.h>
// EEPROM library
#include <EEPROM.h>
// https://arduino.stackexchange.com/questions/79739/74hc595-to-4-digit-7-segment-using-sevsegshift-library

// LCD Nokia 5110
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// SHIFT REGISTER
#define SHIFT_PIN_SHCP 6
#define SHIFT_PIN_STCP 5
#define SHIFT_PIN_DS 4
#define PRLN(x) Serial.println(x)
#define PR(x)        \
    Serial.print(x); \
    Serial.print(" ")

// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 8, 7, 3, 2);

int rotatetext = 1;

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, 1, true);

byte numDigits = 4;
byte digitPins[] = { 12, 11, 10, 9 };            // These are the PINS of the ** Arduino **
byte segmentPins[] = { 0, 1, 2, 3, 4, 5, 6, 7 }; // these are the PINs of the ** Shift register **
bool resistorsOnSegments = false;              // 'false' means resistors are on digit pins
byte hardwareConfig = COMMON_CATHODE;          // See README.md for options

bool updateWithDelays = false; // Default 'false' is Recommended
bool leadingZeros = false;     // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = false;  // Use 'true' if your decimal point doesn't exist or isn't connected

// RNG 
//generates pseudo random series of numbers 0...RAND_MAX - 1 with uniform distribution, starting with 0

unsigned const long A = 1331234;
unsigned const long C = 62284;
const RAND_MAX = 100000;
unsigned long R = 324;

void rng()
{
    R = (R * A + C) % RAND_MAX;
}

int random_number(int min, int max)
{
    rng();
    return (R % (max - min)) + min;
}


typedef struct task
{
    int state;
    unsigned long period;
    unsigned long elapsedTime;

    int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];
// generate random number
int RANDOM;
int answers[3];
int real_answer;
int selecting;

int running = 1;
int const wait_time = 5000;
unsigned long start_wait;
int counter = 0;
int speed = 1;
int score = 0;
int level = 1;
int high_score;
int tolereance = 300;
unsigned long last_increment;
unsigned long last_sample;
int const SAMPLE_PERIOD = 200;
int won = 0;
int brightness = 100;
unsigned long last_brightness;
int avoid_repeated = 0;
int a0, a1;
int last_a0, last_a1;
int playing_mode = 0;
int time_quizz[] = { 0, 20000, 15000 };
int time_left = 0;
int signs[] = { 0, 0, 0 }; // 0 = +, 1 = -, 2 = *
unsigned long quizz_timer = 0;

// int LEFT, RIGHT;
void writeEEPROM(int address, int number)
{
    EEPROM.write(address, number >> 8);
    EEPROM.write(address + 1, number & 0xFF);
}

int readEEPROM(int address)
{
    byte byte1 = EEPROM.read(address);
    byte byte2 = EEPROM.read(address + 1);
    return (byte1 << 8) + byte2;
}

void displayMenuItem(String item, int position, boolean selected)
{
    if (selected)
        display.setTextColor(WHITE, BLACK);
    else
        display.setTextColor(BLACK, WHITE);
    display.setCursor(0, position);
    display.print(">" + item);
}

void display_lcd(char* str)
{
    // Clear the buffer.
    display.clearDisplay();

    // Display Text
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 0);
    display.println(str);
    display.display();
}

void create_quizz()
{
    if (playing_mode == 0) {
        // only addition is used 
        signs[0] = 0;
        signs[1] = 0;
        signs[2] = 0;
    } else if (playing_mode == 1) {
        // addition and substraction are used random_number
        signs[0] = random_number(0, 2);
        signs[1] = random_number(0, 2);
        signs[2] = random_number(0, 2);
    } else if (playing_mode == 2) {
        // all signs are used random_number
        signs[0] = random_number(0, 3);
        signs[1] = random_number(0, 3);
        signs[2] = random_number(0, 3);
    }
    // calculate the sum of the digits
    int sum = 0;
    int temp = RANDOM;
    int a, b, c, d;
    // get digits and save them to the array
    d = temp % 10;
    temp /= 10;
    c = temp % 10;
    temp /= 10;
    b = temp % 10;
    temp /= 10;
    a = temp % 10;

    if (signs[0] == 2 && signs[1] == 2 && signs[2] == 2) {
        sum = a * b * c * d;
    } else if (signs[0] == 2 && signs[1] == 2 && signs[2] == 1) {
        sum = a * b * c - d;
    } else if (signs[0] == 2 && signs[1] == 2 && signs[2] == 0) {
        sum = a * b * c + d;
    } else if (signs[0] == 2 && signs[1] == 1 && signs[2] == 2) {
        sum = a * b - c * d;
    } else if (signs[0] == 2 && signs[1] == 1 && signs[2] == 1) {
        sum = a * b - c - d;
    } else if (signs[0] == 2 && signs[1] == 1 && signs[2] == 0) {
        sum = a * b - c + d;
    } else if (signs[0] == 2 && signs[1] == 0 && signs[2] == 2) {
        sum = a * b + c * d;
    } else if (signs[0] == 2 && signs[1] == 0 && signs[2] == 1) {
        sum = a * b + c - d;
    } else if (signs[0] == 2 && signs[1] == 0 && signs[2] == 0) {
        sum = a * b + c + d;
    } else if (signs[0] == 1 && signs[1] == 2 && signs[2] == 2) {
        sum = a - b * c * d;
    } else if (signs[0] == 1 && signs[1] == 2 && signs[2] == 1) {
        sum = a - b * c - d;
    } else if (signs[0] == 1 && signs[1] == 2 && signs[2] == 0) {
        sum = a - b * c + d;
    } else if (signs[0] == 1 && signs[1] == 1 && signs[2] == 2) {
        sum = a - b - c * d;
    } else if (signs[0] == 1 && signs[1] == 1 && signs[2] == 1) {
        sum = a - b - c - d;
    } else if (signs[0] == 1 && signs[1] == 1 && signs[2] == 0) {
        sum = a - b - c + d;
    } else if (signs[0] == 1 && signs[1] == 0 && signs[2] == 2) {
        sum = a - b + c * d;
    } else if (signs[0] == 1 && signs[1] == 0 && signs[2] == 1) {
        sum = a - b + c - d;
    } else if (signs[0] == 1 && signs[1] == 0 && signs[2] == 0) {
        sum = a - b + c + d;
    } else if (signs[0] == 0 && signs[1] == 2 && signs[2] == 2) {
        sum = a + b * c * d;
    } else if (signs[0] == 0 && signs[1] == 2 && signs[2] == 1) {
        sum = a + b * c - d;
    } else if (signs[0] == 0 && signs[1] == 2 && signs[2] == 0) {
        sum = a + b * c + d;
    } else if (signs[0] == 0 && signs[1] == 1 && signs[2] == 2) {
        sum = a + b - c * d;
    } else if (signs[0] == 0 && signs[1] == 1 && signs[2] == 1) {
        sum = a + b - c - d;
    } else if (signs[0] == 0 && signs[1] == 1 && signs[2] == 0) {
        sum = a + b - c + d;
    } else if (signs[0] == 0 && signs[1] == 0 && signs[2] == 2) {
        sum = a + b + c * d;
    } else if (signs[0] == 0 && signs[1] == 0 && signs[2] == 1) {
        sum = a + b + c - d;
    } else if (signs[0] == 0 && signs[1] == 0 && signs[2] == 0) {
        sum = a + b + c + d;
    }
    PR("sum: ");
    PR(sum);
    // PR signs
    PR("signs: ");
    PR(signs[0]);
    PR(signs[1]);
    PR(signs[2]);
    // PR a b c d
    PR("a b c d: ");
    PR(a);
    PR(b);
    PR(c);
    PR(d);
    PRLN();

    // calculate the sum
    answers[0] = sum;
    real_answer = sum;
    // create two false answers
    int offset = random_number(1, 10);
    int false_answer;
    if (random_number(0, 2))
    {
        false_answer = sum + offset;
    } else
    {
        false_answer = sum - offset;
    }
    answers[1] = false_answer;

    offset = random_number(1, 10);
    if (random_number(0, 2))
    {
        false_answer = sum + offset;
    } else
    {
        false_answer = sum - offset;
    }
    answers[2] = false_answer;
    // randomlly swap the answers
    for (int i = 0; i < 3; i++)
    {
        int j = random_number(0, 3);
        j = random_number(0, 3);
        int temp = answers[i];
        answers[i] = answers[j];
        answers[j] = temp;
    }
}

String get_sign(int sign)
{
    if (sign == 0)
    {
        return String("+");
    } else if (sign == 1)
    {
        return String("-");
    } else if (sign == 2)
    {
        return String("*");
    }
}

void show_quizz()
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.drawFastHLine(0, 10, 83, BLACK);
    String s = "a" + get_sign(signs[0]) + "b" + get_sign(signs[1]) + "c" + get_sign(signs[2]) + "d" + "=?";
    // display.println("a+b+c+d=?");
    display.println(s);

    // add answer to the string
    for (int i = 0; i < 3; i++)
    {
        String num = String(answers[i]);
        displayMenuItem(num, 5 + 10 * (i + 1), selecting == i);
    }
    display.display();
}

void select_playing_mode()
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.println("PLAYING MODE ");
    display.drawFastHLine(0, 10, 83, BLACK);
    displayMenuItem("Easy", 15, selecting == 0);
    displayMenuItem("Medium", 25, selecting == 1);
    displayMenuItem("Hard", 35, selecting == 2);
    display.display();
}

void view_high_score()
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.println("HIGH SCORE");
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(0, 15);
    display.print(String(high_score));
    displayMenuItem("Quit", 35, selecting == 0);
    display.display();

    // displayMenuItem("Medium", 25, selecting == 1);
}

void select_game_over()
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    if (won) {
        display.println("Victory!");
    } else
    {
        display.println("Game Over!");
    }
    display.drawFastHLine(0, 10, 83, BLACK);
    display.setCursor(0, 15);
    display.print("Score: " + String(score));

    if (won) {
        displayMenuItem("Level " + String(level), 25, selecting == 0);
    } else {
        displayMenuItem("Retry level " + String(level), 25, selecting == 0);
    }
    displayMenuItem("Quit", 35, selecting == 1);
    display.display();
}

void main_menu()
{
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, 0);
    display.drawFastHLine(0, 10, 83, BLACK);
    display.println("MAIN MENU :");
    // add answer to the string
    displayMenuItem("Play Now!", 15, selecting == 0);
    displayMenuItem("High Score", 25, selecting == 1);
    display.display();
}

enum GameState
{
    SM1_INIT,
    GameOver,
    CountingDown,
    GameStart,
    Playing,
    Quizz,
    HighScore,
    PlayingMode,
};

void log()
{
    Serial.println("HI!");
}

void log2()
{
    Serial.println("HI!2");
}

void sample()
{
    if (millis() - last_sample > SAMPLE_PERIOD)
    {
        a1 = digitalRead(A1);
        a0 = digitalRead(A0);
        last_sample = millis();
    }
}

void reset_a0a1()
{
    a0 = 0;
    a1 = 0;
}

int quizz_created = 0;

int GameState_Tick(int state1) {
    // PRLN(a0);
    // PR(state1);
    // PR(Playing);
    // PRLN("");
    sample();
    switch (state1)
    { // State transitions
    case SM1_INIT:
        score = 0;
        level = 1;
        main_menu();
        if (a0 || a1)
        {
            if (a1 && !avoid_repeated)
            {
                selecting++;
                selecting %= 2;
            }
            if (a0 && !avoid_repeated)
            {
                if (selecting == 0)
                {
                    state1 = PlayingMode;
                }
                if (selecting == 1)
                {
                    state1 = HighScore;
                    // high_score = readEEPROM(0);

                }
                selecting = 0;
            }
            avoid_repeated = 1;
        } else
            avoid_repeated = 0;
        break;

    case HighScore:
        view_high_score();
        // PRLN(high_score);
        if (a0 || a1)
        {
            if (a1 && !avoid_repeated)
            {
                // selecting++;
                // selecting %= 1;
                state1 = SM1_INIT;
            }
            if (a0 && !avoid_repeated)
            {
                state1 = SM1_INIT;
            }
            avoid_repeated = 1;
        } else
            avoid_repeated = 0;

        break;

    case PlayingMode:
        select_playing_mode();
        if (a0 || a1)
        {
            if (a1 && !avoid_repeated)
            {
                selecting++;
                selecting %= 3;
            }
            if (a0 && !avoid_repeated)
            {
                playing_mode = selecting;
                if (selecting == 1)
                {
                    speed = 2;
                } else if (selecting == 2)
                {
                    speed = 3;
                } else if (selecting == 0)
                {
                    speed = 1;
                }
                time_left = time_quizz[playing_mode];
                state1 = GameStart;
                selecting = 0;
            }
            avoid_repeated = 1;
        } else
            avoid_repeated = 0;
        break;

    case GameStart:
        // PRLN(playing_mode);
        time_left = time_quizz[playing_mode];
        counter = 0;
        won = 0;
        quizz_created = 0;
        selecting = 0;
        brightness = 100;
        sevseg.setBrightness(100);
        RANDOM = random_number(0, 9999);
        start_wait = millis();
        if (playing_mode == 0)
        {
            state1 = Quizz;
        } else
        {
            display_lcd("You have 5 seconds to remember the code ... ");
            state1 = CountingDown;
        }
        break;

    case CountingDown:
        // PR(millis());
        // PR(start_wait);
        // PRLN(wait_time);
        if (millis() - start_wait > wait_time)
        {
            state1 = Quizz;
        }
        break;

    case Quizz:
        if (!quizz_created)
        {
            create_quizz();
            show_quizz();
            quizz_created = 1;
            quizz_timer = millis();
        }
        if (playing_mode != 0 && time_left < (millis() - quizz_timer)) {
            won = 0;
            state1 = GameOver;
        }
        if (a0 || a1)
        {
            if (a1 && !avoid_repeated)
            {
                selecting++;
                selecting %= 3;
                show_quizz();
            }
            if (a0 && !avoid_repeated)
            {
                if (answers[selecting] == real_answer)
                {
                    display_lcd("Correct!!! Now press that button at the right moment !");
                    state1 = Playing;
                } else
                {
                    // display_lcd("Wrong answer! Press any button to play again ...");
                    won = 0;
                    state1 = GameOver;
                }
            }
            avoid_repeated = 1;
        } else
            avoid_repeated = 0;
        break;

    case Playing:
        // PRLN("Playing");
        if (a0 || a1)
        {
            if (avoid_repeated)
                break;
            if (abs(RANDOM - counter) < tolereance)
            {
                // display_lcd("You won! Press any button to continue ...");
                won = 1;
            } else {
                // display_lcd("Game Over! Press any button to play again ...");
                won = 0;
            }
            level += won;
            int bonus = max(tolereance - abs(RANDOM - counter), 0);
            score += (int)(bonus * (1 + speed * 0.4) * (1 + playing_mode));
            if (score > high_score)
            {
                high_score = score;
                writeEEPROM(0, high_score);
            }
            state1 = GameOver;
            selecting = 0;
            reset_a0a1();
        } else
        {
            avoid_repeated = 0;
        }
        break;

    case GameOver:
        select_game_over();
        if (a0 || a1) {
            if (a1 && !avoid_repeated) {
                selecting++;
                selecting %= 2;
            }
            if (a0 && !avoid_repeated) {
                // playing_mode = selecting;
                if (selecting == 0)
                {
                    if (won) {
                        // next_level
                        speed++;
                    } else {
                        // retry 
                        // remove score
                        score = (int)(score * 0.7);
                    }
                    state1 = GameStart;
                } else {
                    state1 = SM1_INIT;
                }
                selecting = 0;
            }
            avoid_repeated = 1;
        } else
            avoid_repeated = 0;
        // if (a0 || a1)
        // {
        //     if (avoid_repeated)
        //         break;
        //     state1 = SM1_INIT;
        // }
        // else
        // {
        //     avoid_repeated = 0;
        // }
        break;

    default:
        PRLN("BUG");
        break;
    }

    switch (state1)
    { // State Action
    case SM1_INIT:
        break;

    case GameOver:
        // sevseg.setNumber(9999);
        if (!won)
        {
            if (millis() - last_brightness > 10)
            {
                // counter++;
                brightness = brightness + 1;
                brightness = min(brightness, 200);
                sevseg.setBrightness(brightness);
                last_brightness = millis();
            }
        }
        sevseg.setNumber(counter);
        sevseg.refreshDisplay();
        break;

    case Playing:
        if (millis() - last_increment > 2) {
            counter += speed;
            last_increment = millis();
        }
        sevseg.setNumber(counter);
        sevseg.refreshDisplay();
        break;

    case Quizz:
        if (playing_mode == 0)
        {
            sevseg.setNumber(RANDOM);
            sevseg.refreshDisplay();
        } else {
            // float tmp = (time_left - millis() + quizz_timer) / 1000;
            float tmp = time_left - (millis() - quizz_timer);
            tmp /= 1000;
            sevseg.setNumberF(tmp, 2);
            sevseg.refreshDisplay();
        }
        break;

    case CountingDown:
        sevseg.setNumber(RANDOM);
        sevseg.refreshDisplay();
        break;
    }

    return state1;
}

void setup()
{
    Serial.begin(9600);
    // NOkia display
    // Initialize Display
    display.begin();

    // you can change the contrast around to adapt the display for the best viewing!
    display.setContrast(57);

    //    display.clearDisplay();
    // Shift
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
    sevseg.setBrightness(100);

    RANDOM = random_number(0, 9999);

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    unsigned char i = 0;
    tasks[i].state = SM1_INIT;
    tasks[i].period = 1;
    tasks[i].elapsedTime = 0;
    tasks[i].TickFct = &GameState_Tick;
    i++;
    high_score = readEEPROM(0);
}

void loop()
{
    // PRLN(tasks[0].state);
    // PRLN(RANDOM);
    // tasks[0].state = GameState_Tick(tasks[0].state);
    for (unsigned char i = 0; i < tasksNum; ++i)
    {
        if ((millis() - tasks[i].elapsedTime) >= tasks[i].period)
        {
            tasks[i].state = tasks[i].TickFct(tasks[i].state);
            tasks[i].elapsedTime = millis(); // Last time this task was ran
        }
    }
}
