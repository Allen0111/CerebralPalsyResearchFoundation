// Author: Jerek Shoemaker
// Last Revision: February 26 2016

#include <SoftwareSerial.h>
#include "SpeechNode.h"

const static byte driveIdentification = 'a';
const static byte speechIdentification = 'x';
const static byte speechHigh = 'y';
const static byte speechLow = 'z';
const static byte speechVerification = 'T';
        
SoftwareSerial bee(2, 3);
SpeechNode speech;

// On startup
void setup()
{
  bee.begin(9600);
  Serial.begin(9600);
  speech.off();
  Serial.println("Talk Ready");
}

// Run over and over
void loop() {

  if(bee.available() > 0)
  {
      speech.setLetter(bee.read());
      if(speech.getLetter() == speechIdentification)
      {
          Serial.println("SpeechMode Active");
          speech.activate();
          bee.write(speechVerification);
      }
      else if(speech.getLetter() == driveIdentification)
      {
          Serial.println("Speech Mode Inactive");
          speech.deactivate();
      }
      else if(speech.getLetter() == speechHigh && speech.isActive())
      {
          Serial.println("HIGH");
          speech.on();
      }
      else if(speech.getLetter() == speechLow && speech.isActive())
      {
          Serial.println("LOW");
          speech.off();
      }
      else
      {
          Serial.println("Command Rejected");
      }
  }
}
