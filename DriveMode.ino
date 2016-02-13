/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: DriveMode.cpp                                                        *
 * Author: Allen Bui                                                                   *
 * Last Revision : October 13, 2015                                                    *
 * Revision No.: ---                                                                   *
 *                                                                                     * 
 *                                                                                     *
 * Copyright (c) 2015 Allen Bui. All rights reserved.                                  *
 *                                                                                     *
 *                                                                                     *
 * DriveMode and all of its accompanying files are free                                *
 * software donated to The Cerebral Palsy Research Foundation:                         *
 * you can redistribute it and/or modify it under the terms of the                     *
 * GNU General Public License as published by the Free Software                        *
 * Foundation.                                                                         *
 *                                                                                     *
 * DriveMode is distributed in the hope that it will be useful,                        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                      *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       *
 * GNU General Public License for more details.                                        *                                             
 *                                                                                     * 
 *                                                                                     *
 * DriveMode encapsulates all of the variables and functions                           *
 * that act as a drive mechanism                                                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "DriveMode.h"
    
//function definitions
DriveMode::DriveMode() {
    driveModeLightPin = 10;
    driveCommPortPin = 6;
    driveMode = 1;
    driveModeActive = false;
    pinMode(driveModeLightPin, OUTPUT);
    pinMode(driveCommPortPin, OUTPUT);
}

DriveMode::~DriveMode() {
}

//accessor definitions
int DriveMode::getDriveCommPortPin() {
    return driveCommPortPin;
}

int DriveMode::getDriveModeLightPin() {
    return driveModeLightPin;
}

int DriveMode::getDriveMode() {
    return driveMode;
}

bool DriveMode::getDriveStatus() {
    return driveModeActive;
}

byte DriveMode::getDriveVerification(){
    return driveVerification;
}

byte DriveMode::getDriveIdentification() {
    return driveIdentification;
}


            
//Control Functions

bool DriveMode::scanForDriveCompletion(int button, SoftwareSerial *xbeeCoordinator) {    // searches for two short presses indicating that 
                                                                //user is finished with drive mode. (high,low, high)
    delay(shortPressTime + shortPressTime);
    if (digitalRead(button) == HIGH) {
      Serial.print("high detected at ");
      Serial.println(+ millis());
        delay(shortPressTime + (shortPressTime * 0.5)); 
        if (digitalRead(button) == LOW) {
          Serial.println("low detected at ");
          Serial.println(millis());
            delay(shortPressTime + (shortPressTime * 0.5));
            if (digitalRead(button)==HIGH) {
              Serial.print("high detected at ");
              Serial.print(millis());
              Serial.println("time to transition");
                return(true);
            }
        }
    }
    else {
        int eval = 1;
        while (eval > 0) {
            if (digitalRead(button) == LOW) {
                if (count == 0) {
                    xbeeCoordinator->write(driveHigh);
                    digitalWrite(driveCommPortPin, HIGH);
                    count++;
                }
                else {
                    count = 1;    //to ensure that count will not exceed the size of an int
                }
            }
            else {
              digitalWrite(driveCommPortPin, LOW);
              xbeeCoordinator->write(driveLow);
              count = 0;
              eval = 0;
              return(false);
            }
        }
    }
    return(false);
}

bool DriveMode::driveModeTransition(SoftwareSerial *xbeeCoordinator, char modeVerification, char modeIdentification) {   //transition from driveMode to speechMode
    myFlush();
    
    xbeeCoordinator->write(modeIdentification);
    delay(25);
    
    if (xbeeCoordinator->read() == modeVerification) {    
        driveModeActive = false;             /*commented out the next four lines and added the two that lie here*/                                         //  digitalWrite (speechCommPort,HIGH);
                                                                                   //  digitalWrite (driveCommPort,LOW);
    }                                                                             //  delay (50);
    else {                                                                       //  digitalWrite (speechCommPort,LOW);
        driveModeActive = true;
    }
    return(!driveModeActive);
}
