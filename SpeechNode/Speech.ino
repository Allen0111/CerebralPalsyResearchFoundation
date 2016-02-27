// Author: Jerek Shoemaker
// Last Revision: February 26 2016

#include <SoftwareSerial.h>
#include "SpeechNode.h"

const static byte driveIdentification = 'a';
const static byte speechIdentification = 'x';
const static byte speechHigh = 'y';
const static byte speechLow = 'z';
const static byte speechVerification = 'T';
const static int  active = 7;
const static int  speechActive = 5;
const static int  driveActive = 6;
        
SoftwareSerial bee(2, 3);
SpeechNode speech;

// On startup
void setup()
{
  pinMode(active, OUTPUT);
  pinMode(speechActive, OUTPUT);
  pinMode(driveActive, OUTPUT);
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
          Serial.println("Speech Mode Active");
          digitalWrite(speechActive, HIGH);
          digitalWrite(driveActive, LOW);
          speech.activate();
          bee.write(speechVerification);
      }
      else if(speech.getLetter() == driveIdentification)
      {
          Serial.println("Speech Mode Inactive");
          digitalWrite(driveActive, HIGH);
          digitalWrite(speechActive, LOW);
          speech.deactivate();
      }
      else if(speech.getLetter() == speechHigh && speech.isActive())
      {
          Serial.println("HIGH");
          digitalWrite(active, HIGH);
          speech.on();
      }
      else if(speech.getLetter() == speechLow && speech.isActive())
      {
          Serial.println("LOW");
          delay(150);
          digitalWrite(active, LOW);
          speech.off();
      }
      else if(speech.getLetter() == 'b' && !speech.isActive())
      {
        digitalWrite(active, HIGH);
      }
      else if(speech.getLetter() == 'c' && !speech.isActive())
      {
        digitalWrite(active, LOW);
      }
      else
      {
          Serial.println("Command Rejected");
      }
  }
}
