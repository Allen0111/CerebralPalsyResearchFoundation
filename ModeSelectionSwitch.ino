/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: ModeSelectionSwitch      (Main)                                      *
 * Author: Allen Bui                                                                   *
 * Last Revision : September 27, 2015                                                  *
 * Revision No.: 2                                                                     *
 *                                                                                     * 
 *                                                                                     * 
 *                                                                                     *
 * ModeSelectionSwitch houses the Main loop where the program begins execution         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include <stdio.h> 
#include <SoftwareSerial.h>
#include "DriveMode.h"
#include "SpeechMode.h"
#include "LightControl.h"
using namespace std;

SoftwareSerial xbeeCoordinator(2, 3);  // Arduino RX, TX (xbeeCoordinator Dout, Din)

const int button = 4;   //button is located at GPIO pin 4

const int  coordinatorStatusLight = 11;

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *  setup function to be executed and initiate   *
 *  all parameters prior to infinite loop        *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */
void setup() {
  
    xbeeCoordinator.begin(9600);   //setup baud rate of xbee
    Serial.begin(9600);
  
    DriveMode driveMode;    //create instances of each object
    SpeechMode speechMode;
    LightControl lightControl;

    static bool driveDesire = false, speechDesire = false;
  
    //setup inputs  
    pinMode(button, INPUT_PULLUP); //Set input port of Button input
      
    //setup outputs
    pinMode(getSpeechModeLight(), OUTPUT);  //LED of speech at pin 9
    pinMode(getDriveModeLight(), OUTPUT);      //LED of speech at pin 10
    pinMode(coordinatorStatusLight, OUTPUT);     //coordinator status light set at pin 11
    
    pinMode(getSpeechCommPort(), OUTPUT);   //speech comm port is located at pin 5
    pinMode(getDriveCommPort(), OUTPUT); //drive comm port is located at pin 6
  
    SelfCheckTest (3);
    
    int currentMode = getSpeechMode();
    
    if (SpeechModeTransition()) {
        printf("successful startup, current mode = speech");
    }
    else {
        emergencyShutdown();
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *     main loop where the main logic sits       *
 *     this program only ends upon detection     *
 *     of an error                               *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */
void loop()
{
    if (xbeeCoordinator.available()) {
        if (digitalRead(button)==LOW){
            switch (RunMode){
            case speechMode:
                xbeeCoordinator.print("MAIN TO SPEECH CHECK!\n");
                speechMode.scanForSpeechCommand(button);
                if (speechDesire == true) {
                      if(speechMode.speechModeTransition()) {
                          lightControl.modeTransitionIndicator(getDriveModeLightPin());
                          currentMode = getSpeechMode();
                      }
                      else {
                         emergencyShutdown();
                      }
                }
                break;
            case driveMode:
                xbeeCoordinator.print("MAIN TO DRIVE CHECK!\n");
                driveMode.scanForDriveCommand(button);
                if (driveDesire == true) {
                    if (driveMode.driveModeTransition()) {
                       lightControl.modeTransitionIndicator(getSpeechModeLightPin);
                       currentMode = getDriveMode(); 
                    }
                    else {
                        emergencyShutDown();
                    }
                }
                break;
            }    
        }
    }
}


//Self Check//
void SelfCheckTest (int y){
  delay (1000);
  for (int x = 0;x < y;x++ ){
    bp (1);
    digitalWrite (speechModeLight,HIGH);
    digitalWrite (driveModeLight,HIGH);
    digitalWrite (statusLight,HIGH);
    delay (500);
    digitalWrite (speechModeLight,LOW);
    digitalWrite (driveModeLight,LOW);
    digitalWrite (statusLight,LOW);
    delay (500);
  }
  digitalWrite (statusLight,HIGH); //Working LED//
}

void bp (int x){
  xbeeCoordinator.print("Transition!\n");
  for (int y = 0; y < x; y++){
    tone (3,1600,120);
    delay (170);
  }
}

