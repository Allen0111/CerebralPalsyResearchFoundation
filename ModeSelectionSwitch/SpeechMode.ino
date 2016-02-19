/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: SpeechMode.cpp                                                       *
 * Author: Allen Bui                                                                   *
 * Last Revision : October 13, 2015                                                    *
 * Revision No.: ---                                                                   *
 *                                                                                     * 
 *                                                                                     *
 * Copyright (c) 2015 Allen Bui. All rights reserved.                                  *
 *                                                                                     *
 *                                                                                     *
 * SpeechMode and all of its accompanying files are free                               *
 * software donated to The Cerebral Palsy Research Foundation:                         *
 * you can redistribute it and/or modify it under the terms of the                     *
 * GNU General Public License as published by the Free Software                        *
 * Foundation.                                                                         *
 *                                                                                     *
 * LightControl is distributed in the hope that it will be useful,                     *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                      *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       *
 * GNU General Public License for more details.                                        *                                             
 *                                                                                     * 
 *                                                                                     *
 * SpeechMode encapsulates all of the variables and functions                          *
 * that act as a speech mechanism                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "SpeechMode.h"

//no arg constructor
SpeechMode::SpeechMode() {
    speechModeLightPin = 9;
    speechMode = 0;
    speechCommPortPin = 5;
    speechModeActive = false;
    pinMode(speechModeLightPin, OUTPUT);
    pinMode(speechCommPortPin, OUTPUT);
    timer = 0;
}

//deconstructor
SpeechMode::~SpeechMode() {
}

//mutator definition
void SpeechMode::changeSpeechMode(bool onOff) {
   speechModeActive = onOff; 
}

//accessor definitions
int SpeechMode::getSpeechModeLightPin() {
    return speechModeLightPin;      
}
    
int SpeechMode::getSpeechMode() {
    return speechMode;        
}      

int SpeechMode::getSpeechCommPortPin() {
    return speechCommPortPin; 
}

bool SpeechMode::getSpeechStatus() {
    return speechModeActive;
}

byte SpeechMode::getSpeechVerification() {
    return speechVerification;
}

byte SpeechMode::getSpeechIdentification() {
    return speechIdentification;
}

void SpeechMode::incrementTimer() {
    timer++;
}

void SpeechMode::resetTimer() {
    timer = 0;
}

bool SpeechMode::scanForSpeechCompletion(int button, SoftwareSerial *xbeeCoordinator) {    // detect when user is done with speech mode by scanning for long press (5 second default)   
    
    resetTimer();
    
    bool completeCheck = false;
    int clickDetector = digitalRead(button);
    
    for(clickDetector; clickDetector == LOW; clickDetector = digitalRead(button)) {
        incrementTimer();
        delay(10);
    }
    
    if (timer > longPressTime){
        completeCheck = true;
    }
    else {
        xbeeCoordinator->write(speechHigh);
        digitalWrite(speechCommPortPin, HIGH);
        delay(110);
        digitalWrite(speechCommPortPin, LOW);
        xbeeCoordinator->write(speechLow);
    }
    return completeCheck;
}


bool SpeechMode::speechModeTransition(SoftwareSerial *xbeeCoordinator, char modeVerification, char modeIdentification) {

    myFlush();

    xbeeCoordinator->write(modeIdentification);
    
    delay(25);
    
    if (xbeeCoordinator->read() == modeVerification) {    
        speechModeActive = false;
               /*commented out the next four lines and added the two that lie here*/
                                      //  digitalWrite (driveCommPort,HIGH);
                                                                                    //  digitalWrite (speechCommPort,LOW);
    }                                                                              //  delay (50);
    else {                                                                        //  digitalWrite (driveCommPort,LOW);
        speechModeActive = true;                                                //  digitalWrite (speechModeLight,HIGH);
    }                                                                           //  digitalWrite (driveModeLight,LOW);
    return(!speechModeActive);
}
