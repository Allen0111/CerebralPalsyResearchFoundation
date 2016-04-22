
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                 *
 * Copyright (c) 2015 Allen Bui. <Allen.Bui.0111@gmail.com                         *
 *                                                                                 *
 *                                                                                 *
 * ModeSelectionSwitch and all of its accompanying files are free                  *
 * software donated to The Cerebral Palsy Research Foundation:                     *
 * you can redistribute it and/or modify it under the terms of the                 *
 * GNU General Public License as published by the Free Software                    *
 * Foundation                                                                      *
 *                                                                                 *  
 * The above copyright notice and this permission notice shall be                  * 
 * included in all copies or substantial portions of the Software.                 *                                                                                 *
 * ModeSelectionSwitch is distributed in the hope that it will be useful.          *
 *                                                                                 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,                 *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF              * 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT           *                                                                     * 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE                           * 
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION          * 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION           * 
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 *                   
 *                                                                                 * 
 * See the GNU General Public License for more details.                            *
 *                                                                                 * 
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Document Name: SpeechMode.cpp                                                       
 * Author: Allen Bui                                                                   
 * Last Revision : April 22, 2016                                                   
 * Revision No.: ---                                                                    
 *                                                                                     
 * MODIFICATION NOTES: 4/22/2016 - ADDED WATCHDOG TIMER RESET METHOD                                                                                     
 *                                                                                     
 * SpeechMode encapsulates all of the variables and functions                          
 * that act as a speech mechanism                                                      
 */

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
    
    for(clickDetector; clickDetector == HIGH; clickDetector = digitalRead(button)) {
        incrementTimer();
        wdt_reset();
        delay(10);
    }
    
    if (timer > longPressTime){
        completeCheck = true;
    } else {
        if (!firstClick) {
            xbeeCoordinator->write(speechHigh);
            transmitCount++;
            Serial.println("LOW");
            delay(110);
            Serial.println("HIGH");
            xbeeCoordinator->write(speechLow);
            transmitCount++;
        } else {
            firstClick = false;
        }
    }
    return completeCheck;
}


bool SpeechMode::speechModeTransition(SoftwareSerial *xbeeCoordinator, char modeVerification, char modeIdentification) {

    myFlush();

    xbeeCoordinator->write(modeIdentification);
    transmitCount++;
    //delay(25);
    
    //if (xbeeCoordinator->read() == modeVerification) {    
        speechModeActive = false;
               /*commented out the next four lines and added the two that lie here*/
                                      //  digitalWrite (driveCommPort,HIGH);
                                                                                    //  digitalWrite (speechCommPort,LOW);
  //  }                                                                              //  delay (50);
   // else {                                                                        //  digitalWrite (driveCommPort,LOW);
     //   speechModeActive = true;                                                //  digitalWrite (speechModeLight,HIGH);
   // }                                                                           //  digitalWrite (driveModeLight,LOW);
    //return(!speechModeActive);
    return true;
}

void SpeechMode::setFirstClick() {
  firstClick = true;
}

