/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: LightControl.cpp                                                     *
 * Author: Allen Bui                                                                   *
 * Last Revision : October 13, 2015                                                    *
 * Revision No.: ---                                                                   *
 *                                                                                     * 
 *                                                                                     *
 * Copyright (c) 2015 Allen Bui. All rights reserved.                                  *
 *                                                                                     *
 *                                                                                     *
 * LightControl and all of its accompanying files are free                             *
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
 * LightControl encapsulates all of the variables and functions                        *
 * that act as an LED indicator                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
LightControl::LightControl() {
    loopForTrue = 3;
    loopForTransition = 10;
}

LightControl::~LightControl() {  
}


void LightControl::coordinatorStatusTrue(int coordinatorStatusLight) {
    digitalWrite(coordinatorStatusLight, HIGH);
}

void LightControl::selfCheckTrue (int lightPin){   //function that indicates positive construction of a particular mode within the system.    
    for (int loopCount = 0; loopCount < loopForTrue; loopCount++ ){
        digitalWrite(lightPin,HIGH);
        delay(250);
        digitalWrite(lightPin,LOW);
        delay(250);
        digitalWrite(lightPin,HIGH);
        delay(250);
        digitalWrite(lightPin,LOW);
    }
}

//LED transition flash sequence//  
void LightControl::modeTransitionIndicator(int goFromLightPin, int goToLightPin){  
    for (int loopCount = 0; loopCount < loopForTransition; loopCount++) {
        digitalWrite (goToLightPin, HIGH);
        delay (300 - (sin(loopCount * 0.146) * 290));
        digitalWrite (goToLightPin, LOW);
        delay (300 - (sin (loopCount * 0.146) * 300));
    }    
    delay(50);
    digitalWrite(goToLightPin,HIGH);
    digitalWrite(goFromLightPin,LOW);
}
