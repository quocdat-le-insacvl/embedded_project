/*
 * 
 * Programme pour capturer la Température et l'humidité via un DHT11 et l'afficher sur un écran LCD
 * 
 */

// include the library code:
#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define PINBUTTON 4

bool currentState = false;

DHT dht(DHTPIN, DHTTYPE);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void Affiche()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  boolean etatBouton=digitalRead(PINBUTTON);
  if(currentState == false) // on est dans l'affichage de Température
  {
    if(etatBouton == false) // on n'a pas appuyé sur le bouton, on ne change pas d'état
    {
      lcd.setCursor(0,0);
      lcd.print("Temperature");
      lcd.setCursor(0, 1);
      lcd.print(t);
    }
    else  // on a appuyé sur le bouton => changement d'état
    {
      lcd.setCursor(0,0);           // on efface l'écran et on change le message
      lcd.print("                 ");
      lcd.setCursor(0,1);
      lcd.print("                 ");

      lcd.setCursor(0,0);
      lcd.print("Humidité");
      lcd.setCursor(0, 1);
      lcd.print(h);
      currentState = true;
    }
  }
  else
  {
    if(etatBouton == false) // on n'a pas appuyé sur le bouton, on ne change pas d'état
    {
      lcd.setCursor(0,0);
      lcd.print("Humidité");
      lcd.setCursor(0, 1);
      lcd.print(h);
    }
    else  // on a appuyé sur le bouton => changement d'état
    {
      lcd.setCursor(0,0);           // on efface l'écran et on change le message
      lcd.print("                 ");
      lcd.setCursor(0,1);
      lcd.print("                 ");

      lcd.setCursor(0,0);
      lcd.print("Temperature");
      lcd.setCursor(0, 1);
      lcd.print(t);
      currentState = false;
    }
  }
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Print a message to the LCD.
  lcd.print("Hello, World!");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("                 ");
  dht.begin();
  pinMode(PINBUTTON,INPUT);
}

void loop() {
  Affiche();
 
  delay(200);

}

