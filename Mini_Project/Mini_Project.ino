/* -------------------------------------------------------------------------- */
/*                                 Main Header                                */
/* -------------------------------------------------------------------------- */

/* --------------------------------- Imports -------------------------------- */

#include <EIRremote.h>
#include <EIRremoteInt.h>

/* -------------------------------------------------------------------------- */

/* ----------------------------- Global Vaibles ----------------------------- */

int IRPin = 4;

IRrecv myIR(IRPin);
decode_results results;

/* -------------------------------------------------------------------------- */

void setup()
{
  // put your setup code here, to run once:

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
    Serial.println("VOL+");
    break;

  //Volume Down Case
  case 0xFFA857:
    Serial.println("VOL-");
    break;

  //Rewind Case
  case 0xFF22DD:
    Serial.println("REWIND");
    break;

  //Fast Forward Case
  case 0xFFC23D:
    Serial.println("FAST FORWARD");
    break;
  }
  delay(500);
}

/* -------------------------------------------------------------------------- */
