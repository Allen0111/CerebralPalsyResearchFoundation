/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *-
 * Document Name: ModeSelectionSwitch      (Main)                                  *
 * Author: Allen Bui                                                               *
 * Last Revision : Februay 11, 2016                                                *
 * Revision No.:  A                                                                *
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

SoftwareSerial xbeeCoordinator(2, 3);  // Arduino RX, TX (xbeeCoordinator Dout, Din)

const int button = 4;                         //input button is located at GPIO pin 4
const int  coordinatorStatusLight = 11;   //coordinator GPIO pin is located at pin 11

static int checkMode = 0;
static bool driveDesire = false, speechDesire = false;

enum mode {SPEECH = 0, DRIVE};
void emergencyShutdown();

//create instances
//LightControl lightControl;
DriveMode driveMode;
SpeechMode speechMode;

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 *  setup function to be executed and initiate   *
 *  all parameters prior to infinite loop        *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */
void setup() {
    //lightControl.selfCheckTrue(driveMode.getDriveModeLightPin());   //will indicate a successful construction of DriveMode, does not indicate status
    //lightControl.selfCheckTrue(speechMode.getSpeechModeLightPin());     //will indicate a successful construction of SpeechMode
        
    xbeeCoordinator.begin(9600);   //setup baud rate of xbee
    Serial.begin(9600);

    //setup inputs  
    pinMode(button, INPUT_PULLUP); //Set input port of Button input
    pinMode(coordinatorStatusLight, OUTPUT);     //coordinator status light set at pin 11
    
    checkMode = speechMode.getSpeechMode();


    Serial.println("initiating");
    if (driveMode.driveModeTransition(&xbeeCoordinator, speechMode.getSpeechVerification(), speechMode.getSpeechIdentification())) {
        //xbeeCoordinator.print("successful startup, current mode = speech\n");
        //SPEECHMODE == TRUE;
        //lightControl.modeTransitionIndicator(driveMode.getDriveModeLightPin(), speechMode.getSpeechModeLightPin());
        //lightControl.coordinatorStatusTrue(coordinatorStatusLight);
    } else {
        //xbeeCoordinator.print("emergency shutdown\n");
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
void loop() {

    if (xbeeCoordinator.isListening()) {
        if (digitalRead(button) == LOW) {
            switch(checkMode){
            case(SPEECH):
                driveDesire = speechMode.scanForSpeechCompletion(button, &xbeeCoordinator);
                if (driveDesire == true) {
                      if (speechMode.speechModeTransition(&xbeeCoordinator, driveMode.getDriveVerification(), driveMode.getDriveIdentification())) {
                          //lightControl.modeTransitionIndicator(speechMode.getSpeechModeLightPin(), driveMode.getDriveModeLightPin());
                          //DRIVE MODE == TRUE
                          checkMode = driveMode.getDriveMode();
                          driveDesire = false;
                      }
                      else {
                          //xbeeCoordinator.print("Emergency Shutdown\n");
                          emergencyShutdown();
                      }
                }
                break;
            case(DRIVE):
                speechDesire = driveMode.scanForDriveCompletion(button, &xbeeCoordinator);
                if (speechDesire == true) {
                    if (driveMode.driveModeTransition(&xbeeCoordinator, speechMode.getSpeechVerification(), speechMode.getSpeechIdentification())) {
                        //SPEECH MODE == TRUE
                        //lightControl.modeTransitionIndicator(driveMode.getDriveModeLightPin(), speechMode.getSpeechModeLightPin());
                        checkMode = speechMode.getSpeechMode(); 
                        speechDesire = false;
                    }
                    else {
                        //xbeeCoordinator.print("Emergency Shutdown\n");
                        emergencyShutdown();
                    }
                }
                break;
            }    
        }
    }
}

void emergencyShutdown() {
  Serial.println("shutdown");
    //can only be implemented once the hardware is setup
}

void myFlush() {
    char garbageCollector;
    while (xbeeCoordinator.available()) {
        garbageCollector = xbeeCoordinator.read();
    }
}

