/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: ModeSelectionSwitch      (Main)                                  *
 * Author: Allen Bui                                                               *
 * Last Revision : October 08, 2015                                                *
 * Revision No.: ---                                                               *
 *                                                                                 * 
 *                                                                                 *
 * Copyright (c) 2015 Allen Bui. All rights reserved.                              *
 *                                                                                 *
 *                                                                                 *
 * ModeSelectionSwitch and all of its accompanying files are free                  *
 * software donated to The Cerebral Palsy Research Foundation:                     *
 * you can redistribute it and/or modify it under the terms of the                 *
 * GNU General Public License as published by the Free Software                    *
 * Foundation                                                                      *
 *                                                                                 *
 * ModeSelectionSwitch is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   *
 * GNU General Public License for more details.                                    *
 *                                                                                 * 
 *                                                                                 *
 * ModeSelectionSwitch houses the Main loop where the program begins execution     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include <stdio.h> 
#include <SoftwareSerial.h>
#include "DriveMode.h"
#include "SpeechMode.h"
#include "LightControl.h"
using namespace std;

SoftwareSerial xbeeCoordinator(2, 3);  // Arduino RX, TX (xbeeCoordinator Dout, Din)

const int button = 4;                         //input button is located at GPIO pin 4
const int  coordinatorStatusLight = 11;   //coordinator GPIO pin is located at pin 11

static int checkMode = 0;
static bool driveDesire = false, speechDesire = false;

enum mode {SPEECH = 0, DRIVE};
void emergencyShutdown();

//create instances
LightControl lightControl;
DriveMode driveMode;
SpeechMode speechMode;

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *  setup function to be executed and initiate   *
 *  all parameters prior to infinite loop        *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */
void setup() {
    
    lightControl.selfCheckTrue(driveMode.getDriveModeLightPin());   //will indicate a successful construction of DriveMode, does not indicate status
    lightControl.selfCheckTrue(speechMode.getSpeechModeLightPin());     //will indicate a successful construction of SpeechMode
        
    xbeeCoordinator.begin(9600);   //setup baud rate of xbee
    Serial.begin(9600);

    //setup inputs  
    pinMode(button, INPUT_PULLUP); //Set input port of Button input
    pinMode(coordinatorStatusLight, OUTPUT);     //coordinator status light set at pin 11
    
    checkMode = getSpeechMode();
    
    if (speechModeTransition()) {
        printf("successful startup, current mode = speech");
    } else {
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
        if (digitalRead(button) == LOW){
            switch(checkMode){
            case(SPEECH):
                xbeeCoordinator.print("MAIN TO SPEECH COMPLETION CHECK!\n");
                driveDesire = speechMode.scanForSpeechCompletion(button);
                if (driveDesire == true) {
                      if(driveDesire.changeSpeechMode()) {
                          lightControl.modeTransitionIndicator(driveMode.getDriveModeLightPin());
                          checkMode = speechMode.getSpeechMode();
                          driveDesire = false;
                      }
                      else {
                         emergencyShutdown();
                      }
                }
                break;
            case(DRIVE):
                xbeeCoordinator.print("MAIN TO DRIVE COMPLETION CHECK!\n");
                speechDesire = driveMode.scanForDriveCompletion(button);
                if (speechDesire == true) {
                    if (driveMode.driveModeTransition()) {
                       lightControl.modeTransitionIndicator(speechMode.getSpeechModeLightPin);
                       checkMode = driveMode.getDriveMode(); 
                       speechDesire = false;
                    }
                    else {
                        emergencyShutdown();
                    }
                }
                break;
            }    
        }
    }
}

void emergencyShutdown(){
    //can only be implemented once the hardware is setup
}
