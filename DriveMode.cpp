/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: DriveMode.cpp                                                        *
 * Author: Allen Bui                                                                   *
 * Last Revision : October 08, 2015                                                    *
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
using namespace std;
    
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


//mutator definition
void DriveMode::changeDriveMode(bool onOff) {
   driveModeActive = onOff; 
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


//Control Functions

bool DriveMode::scanForDriveCompletion(int button) {    // searches for two short presses indicating that 
                                                                //user is finished with drive mode. (high,low, high)
    delay(shortPressTime);
    xbeeCoordinator.print("Detect Drive Mode with Double Click!\n");
    if (digitalRead(button) == HIGH) {
        delay(shortPressTime * shortPressTime);
        if (digitalRead(button) == LOW) {
            delay(shortPressTime * shortPressTime);
            if (digitalRead(button)==HIGH) {
                return(true);
            }
        }
    }
    return(false);
}

bool DriveMode::driveModeTransition() {   //transition from driveMode to speechMode
  driveModeActive = true;

  digitalWrite (speechCommPort,HIGH);
  digitalWrite (driveCommPort,LOW);
  delay (50);
  digitalWrite (speechCommPort,LOW);
  digitalWrite (driveModeLight,HIGH);
  digitalWrite (speechModeLight,LOW);
  return(true);
}
