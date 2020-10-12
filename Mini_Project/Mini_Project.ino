/* -------------------------------------------------------------------------- */
/*                                 Main Header                                */
/* -------------------------------------------------------------------------- */

/* --------------------------------- Imports -------------------------------- */

#include <EIRremote.h>
#include <EIRremoteInt.h>
#include <Servo.h>

/* -------------------------------------------------------------------------- */

/* ----------------------------- Global Vaibles ----------------------------- */

int IRPin = 4;

int motorFront = 6;
int motorBack = 5;

int servoPin = 10;
int servoPosition = 90;

IRrecv myIR(IRPin);
decode_results results;

Servo myServo;

/* -------------------------------------------------------------------------- */

void setup()
{
  


/** This line uses the attach function in the servo object we imported to set
   * which pin the servo uses. In this case we are using a global variable 
   * called servoPin.
   */
  myServo.attach(servoPin);




  pinMode(IRPin, INPUT);
  myIR.enableIRIn();


  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (myIR.decode(&results))
  {
    Serial.println(results.value, HEX);
    translateIR();
    myIR.resume();
  }
}

/* -------------------------- Translate IR Function ------------------------- */

void translateIR()
{ // takes action based on IR code received
  switch (results.value)
  {

  //Volume Up Case
  case 0xFF629D:
    Serial.println("VOL+ and DC Forward");
    analogWrite(motorFront, 255);
    delay(2000);
    analogWrite(motorFront, 0);
    break;

  //Volume Down Case
  case 0xFFA857:
    Serial.println("VOL-");
    analogWrite(motorBack, 255);
    delay(2000);
    analogWrite(motorBack, 0);
    break;

  //Rewind Case
  case 0xFF22DD:
    Serial.println("REWIND");

    if(myServo.read() > 90)
    {
      servoPosition = 180;

    }
    else if (myServo.read() <= 90 )
    {
      servoPosition = myServo.read() + 90; 
    }
    else
    {
      //do nothing
    }
    myServo.write(servoPosition);
    delay(250);
    break;

  //Fast Forward Case
  case 0xFFC23D:
    Serial.println("FAST FORWARD");

    if(myServo.read() < 90)
    {
      servoPosition = 0;

    }
    else if (myServo.read() >= 90 )
    {
      servoPosition = myServo.read() - 90; 
    }
    else
    {
      //do nothing
    }
    myServo.write(servoPosition);


    delay(250);
    break;
  }

  
  delay(500);
}

/* -------------------------------------------------------------------------- */
