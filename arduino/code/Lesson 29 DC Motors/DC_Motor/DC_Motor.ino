//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/

#define ENABLE 5
#define DIRA 3
#define DIRB 2
#define POT 4
int Vpot=0;
int power = 0;
int i;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}

void loop() {
    power =0;
    Vpot=analogRead(POT);
    Serial.print("Vpot =");
    Serial.println(Vpot);
    if(Vpot >= 480 && Vpot <= 540) // STOP
    {
      Serial.println("STOP");
      analogWrite(ENABLE,0);
      digitalWrite(DIRA,HIGH);
      digitalWrite(DIRB,HIGH);
    }
    else
    {
      if(Vpot < 480) // REVERSE
      {
        Serial.println("REVERSE");
        power=(480-Vpot)+5; // on calcul la valeur de la puissance;
        if(power >=250) // si la valeur calculée est supérieur à 200 alors on passe à la puissance max
        {
          power=255;
        }
        Serial.print("power =");
        Serial.println(power);
        digitalWrite(DIRA,HIGH);
        digitalWrite(DIRB,LOW);
        analogWrite(ENABLE,power);
      }
      else
      {
         if(Vpot > 540) // NORMAL
          {
            Serial.println("NORAML");
            power=(Vpot-540)+10; // idem que pour le reverse
            if(power >=250)
            {
              power=255;
            }
            Serial.print("power =");
            Serial.println(power);
            digitalWrite(DIRA,LOW);
            digitalWrite(DIRB,HIGH);
//            digitalWrite(DIRA,LOW);
//            digitalWrite(DIRB,HIGH);
            analogWrite(ENABLE,power);
          }   
      }
    }
    delay(1000);
}

//---back and forth example
////    Serial.println("One way, then reverse");
////    digitalWrite(ENABLE,HIGH); // enable on
////    for (i=0;i<5;i++) {
////    digitalWrite(DIRA,HIGH); //one way
////    digitalWrite(DIRB,LOW);
////    delay(500);
////    digitalWrite(DIRA,LOW);  //reverse
////    digitalWrite(DIRB,HIGH);
////    delay(500);
////  }
////  digitalWrite(ENABLE,LOW); // disable
////  delay(2000);
//
////  Serial.println("fast Slow example");
////  //---fast/slow stop example
////  digitalWrite(ENABLE,HIGH); //enable on
////  digitalWrite(DIRA,HIGH); //one way
////  digitalWrite(DIRB,LOW);
////  delay(3000);
////  digitalWrite(ENABLE,LOW); //slow stop
////  delay(1000);
////  digitalWrite(ENABLE,HIGH); //enable on
////  digitalWrite(DIRA,LOW); //one way
////  digitalWrite(DIRB,HIGH);
////  delay(3000);
////  digitalWrite(DIRA,LOW); //fast stop
////  delay(2000);

//  Serial.println("PWM full then slow");
//  //---PWM example, full speed then slow
//  analogWrite(ENABLE,255); //enable on
//  digitalWrite(DIRA,HIGH); //one way
//  digitalWrite(DIRB,LOW);
//  delay(20000);
   
