#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object


void setup() {
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0;
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
}
int count = 1;
void loop() {
    sevseg.setNumber(count++);/*display the count value*/
    sevseg.refreshDisplay(); /* refreshing the 7-segment */
    delay(20);
}

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(6, 5, 4, 3, 2);

int rotatetext = 1;

void setup()   {
    Serial.begin(9600);

    //Initialize Display
    display.begin();

    // you can change the contrast around to adapt the display for the best viewing!
    display.setContrast(57);

    // Clear the buffer.
    display.clearDisplay();

    // Display Text
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.println("Hello world!");
    display.display();
    delay(2000);
    display.clearDisplay();


    // Display Inverted Text
    display.setTextColor(WHITE, BLACK); // 'inverted' text
    display.setCursor(0,0);
    display.println("Hello world!");
    display.display();
    delay(2000);
    display.clearDisplay();

    // Scaling Font Size
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.setTextSize(2);
    display.println("Hello!");
    display.display();
    delay(2000);
    display.clearDisplay();

    // Display Numbers
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println(123456789);
    display.display();
    delay(2000);
    display.clearDisplay();

    // Specifying Base For Numbers
    display.setCursor(0,0);
    display.print("0x"); display.print(0xFF, HEX);
    display.print("(HEX) = ");
    display.print(0xFF, DEC);
    display.println("(DEC)");
    display.display();
    delay(2000);
    display.clearDisplay();

    // Display ASCII Characters
    display.setCursor(0,0);
    display.setTextSize(2);
    display.write(3);
    display.display();
    delay(2000);
    display.clearDisplay();

    // Text Rotation
    while(1)
    {
        display.clearDisplay();
        display.setRotation(rotatetext);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
        display.setTextSize(1);
        display.setTextColor(BLACK);
        display.setCursor(0,0);
        display.println("Text Rotation");
        display.display();
        delay(1000);
        display.clearDisplay();
        rotatetext++;
    }
}

void loop() {}