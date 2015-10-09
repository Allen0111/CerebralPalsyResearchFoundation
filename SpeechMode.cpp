/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: SpeechMode.cpp                                                       *
 * Author: Allen Bui                                                                   *
 * Last Revision : October 08, 2015                                                    *
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



//no arg constructor
SpeechMode::SpeechMode() {
    speechModeLightPin = 9;
    speechMode = 0;
    speechCommPortPin = 5;
    speechModeActive = false;
    timer = resetTimer();
    pinMode(speechModeLightPin, OUTPUT);
    pinMode(speechCommPortPin, OUTPUT);
}

//deconstructor
SpeechMode::~SpeechMode() {
}


//mutator definition
void changeSpeechMode(bool onOff) {
   speechModeActive = onOff; 
}

//accessor definitions
int getSpeechModeLightPin() {
    return speechModeLightPin;      
}
    
int getSpeechMode() {
    return speechMode;        
}      

int getSpeechCommPortPin() {
    return speechCommPortPin; 
}

bool getSpeechStatus() {
    return speechModeActive;
}


void scanForSpeechCompletion(int button) {    // detect when user is done with speech mode by scanning for long press (5 second default)   
    
    clickDetector = digitalRead(button);
    
    xbeeCoordinator.print("Detect Talk Mode with long press!\n");
    
    for(clickDetector; clickDetector == LOW; clickDetector = digitalRead(button)) {
        incrementTimer();
        delay(20);
    }
    
    if (timer > longPressTime){
        resetTimer();
        Shift_Board_Mode ();
    }
}


bool speechModeTransition() {
  current = driveMode;
  bp (2);
  xbeeCoordinator.print("Talk Mode!\n");
  digitalWrite (driveCommPort,HIGH);
  digitalWrite (speechCommPort,LOW);
  delay (50);
  digitalWrite (driveCommPort,LOW);
  digitalWrite (speechModeLight,HIGH);
  digitalWrite (driveModeLight,LOW);
}


void incrementTimer() {
    timer++;
}

void resetTimer() {
    timer = 0;
}
