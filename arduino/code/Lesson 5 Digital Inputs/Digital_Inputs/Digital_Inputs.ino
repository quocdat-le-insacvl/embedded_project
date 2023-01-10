//www.elegoo.com
//2016.12.08

int ledPin = 5;
int buttonApin = 9;
int buttonBpin = 8;
bool up = false;

byte leds = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}

void loop() 
{
  if (digitalRead(buttonApin) == LOW && !up)
  {
    digitalWrite(ledPin, HIGH);
    up=true;
    Serial.println("on up");
    delay(50);
  }
  else if (digitalRead(buttonApin) == LOW && up)
  {
    digitalWrite(ledPin, LOW);
    up=false;
    Serial.println("On down");
    delay(50);
  }
  delay(100);
 
}
