//Adding Libraries 

#include <SPI.h>                  /* to handle the communication interface with the modem*/
#include <nRF24L01.h>             /* to handle this particular modem driver*/
#include <RF24.h>                 /* the library which helps us to control the radio modem*/

/*
VCC CNS MOSI IRQ
    8   51
GND CE  SCK  MISO
    53   52   50
*/

#define pot_pin A0                /*Variable pin of POT is to be connected to analog pin 0 i.e.A0*/
RF24 radio(53, 8);                /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */
const byte Address[6] = "12345"; /* Address from which data to be received */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pot_pin,INPUT);         /* Setting A0 (POT pin) as input*/
  radio.begin ();                 /* Activate the modem*/
  radio.openWritingPipe (Address); /* Sets the address of transmitter to which program will send the data */
    // radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  // put your main code here, to run repeatedly:
//   radio.stopListening ();          /* Setting modem in transmission mode*/
  int value = analogRead(pot_pin);    /*Reading analog value at pin A0 and storing in varible 'value'*/
  int data = map( value , 0 , 1023 , 0 , 255 );   /* Convering the 10 bit value to 8 bit */
  radio.write(&data, sizeof(data));            /* Sending data over NRF 24L01*/
  Serial.print("Transmitting Data : ");
  Serial.println(data);                           /* Printing POT value on serial monitor*/
  delay(100);
}
