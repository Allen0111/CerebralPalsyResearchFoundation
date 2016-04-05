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
   // driveModeLightPin = 10;
    driveCommPortPin = 4;
    pinMode(driveCommPortPin, OUTPUT);
    driveMode = 1;
    driveModeActive = false;
   //pinMode(driveModeLightPin, OUTPUT);
   // pinMode(driveCommPortPin, OUTPUT);
    timer = millis();
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

    if (timedEdgeDetection(button)) {
        Serial.println("if edge detection");
        return true;
    } else {
      Serial.println("else edge detection");
        int eval = 1;
        while (eval > 0) {
          Serial.println("while loop");
            if (digitalRead(button) == HIGH) {
                        Serial.println("while loop button high");
                if (count == 0) {
                            Serial.println("while loop count is zero");
                    //digitalWrite(output, LOW);
                    xbeeCoordinator->write(driveHigh);
                    digitalWrite(driveCommPortPin, HIGH);
                    transmitCount++;
                    count++;
                }
                else {
                            Serial.println("while loop count is not zero");
                    count = 1;    //to ensure that count will not exceed the size of an int
                }
            }
            else {
              digitalWrite(driveCommPortPin, LOW);
              transmitCount++;
              xbeeCoordinator->write(driveLow);
              //digitalWrite(output, HIGH);
              count = 0;
              eval = 0;
              return(false);
            }
        }
    }
    return(false);
}

bool DriveMode::timedEdgeDetection(int button) {
            Serial.println("timed edge function");
    if (buttonState == LOW) {
        lastButtonState = HIGH;
    } else lastButtonState = LOW;

    if ((millis() - timer) >= allottedTime) {
                Serial.println("time out");
      timer = millis();
      buttonPushCounter = 1;
      //return false;
    }                                                                //else {
   Serial.print("number of button pushes:  ");
            Serial.println(buttonPushCounter);
               
    /*buttonState = digitalRead(button);

    if (buttonState != lastButtonState) {
        if (buttonState == HIGH) {
            buttonPushCounter++;
            Serial.print("number of button pushes:  ");
            Serial.println(buttonPushCounter);   
        } */
        
        //delay(50); // Debounce
        
        if(((millis() - timer) <= allottedTime) && buttonPushCounter >= 2) {
            buttonPushCounter = 0;
            timer = millis();
            return true;
        }
   // }
    
    lastButtonState = buttonState;
                                                         // }
    return false;
}

bool DriveMode::driveModeTransition(SoftwareSerial *xbeeCoordinator, char modeVerification, char modeIdentification) {   //transition from driveMode to speechMode
    myFlush();
    
    xbeeCoordinator->write(modeIdentification);
    transmitCount++;
    delay(25);
    
    //if (xbeeCoordinator->read() == modeVerification) {    
        driveModeActive = false;             /*commented out the next four lines and added the two that lie here*/                                         //  digitalWrite (speechCommPort,HIGH);
                                                                                   //  digitalWrite (driveCommPort,LOW);
    //}                                                                             //  delay (50);
    //else {                                                                       //  digitalWrite (speechCommPort,LOW);
    //    driveModeActive = true;
    //}
    return(!driveModeActive);
}

void DriveMode::resetTimer() {
 
                Serial.println("reset timer and button");
      timer = millis();
      buttonPushCounter = 0;
  
}

void DriveMode::incrementButton() {
  buttonPushCounter++;
}


