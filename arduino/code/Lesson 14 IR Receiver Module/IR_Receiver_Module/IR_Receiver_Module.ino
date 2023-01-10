#include <Servo.h>
#include "IRremote.h"


int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
const int pinServo = 9;

Servo ServoT;

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
String noms[5] = {"90 deg", "179 deg", "0 deg", "Vers 179 deg", "Vers 0 deg"};
int posServo = 90; // variable de position du servomoteur
int ajServo = 0; // variable de déplacement du servomoteur
int nbCode = 0; // numéro de code en cours
unsigned long tpsDep = millis();

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
// describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0"); nbCode=0;    break;
  case 0xFF30CF: Serial.println("1"); nbCode=1;   break;
  case 0xFF18E7: Serial.println("2"); nbCode=2;   break;
  case 0xFF7A85: Serial.println("3"); nbCode=3;   break;
  case 0xFF10EF: Serial.println("4"); nbCode=4;   break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case
  positionServo();

  delay(500); // Do not get immediate repeat


} //END translateIR

//Fonction de positionnement du servomoteur
void positionServo() {
  switch (nbCode) { //en fonction du code
    case 0: // on place le servo à 90°
      ajServo = 0;
      posServo = 90;
      Serial.println("code 0, position 90");
      break;
    case 1: // on place le servo à 179°
      ajServo = 0;
      posServo = 179;
      Serial.println("code 1, position 179");
      break;
    case 2: // on place le servo à 0°
      ajServo = 0;
      posServo = 0;
      Serial.println("code 2, position 0");
      break;
    case 3: // on met la variable de déplacement à 1°
      ajServo = +1;
      Serial.println("code 3, position +1");
      break;
    case 4: // on met la variable de déplacement à -1°
      ajServo = -1; 
      Serial.println("code 3, position -1");
      break;
  }
}

void bougeServo() {
   unsigned long tpsAct = millis(); //temps actuel
  if (tpsAct - tpsDep > 50) { //si 50ms passées
    posServo += ajServo; // on déplace le servo
    tpsDep = tpsAct; //on réinitialise le temps
  }
  if (posServo <= 0 || posServo >= 179) // si servo hors limite
    ajServo = 0; // on stoppe le déplacement
  ServoT.write(posServo); // on envoie la position du servomoteur
}
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  ServoT.attach(pinServo);

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    //translateIR();
    //bougeServo();
    //Serial.print("pos = "); Serial.println(posServo); 
    //irrecv.resume(); // receive the next value
    ServoT.write(0);
    delay(5000);
    ServoT.write(90);
    delay(2000);
  }  
}/* --(end main loop )-- */


