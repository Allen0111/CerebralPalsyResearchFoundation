/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: DriveMode.cpp
 * Author: Allen Bui                                                                  







 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "DriveMode.h"
using namespace std;
 
    
//function definitions
DriveMode::DriveMode() {
  
    driveModeLightPin = 10;
    driveCommPortPin = 6;
    driveMode = 1;
    driveModeActive = false;
}

DriveMode::~DriveMode() {
}


//mutator definition
void changeDriveMode(bool onOff) {
   driveModeActive = onOff; 
}


//accessor definitions
int DriveMode::getDriveCommPortPin() {
    return driveCommPort;
}

int DriveMode::getDriveModeLightPin() {
    return driveModeLight;
}

int DriveMode::getDriveMode() {
    return driveMode;
}

bool getDriveStatus() {
    return driveModeActive;
}


//Control Functions

bool scanForDriveCommand(int button) {    // searches for two two short presses. (high,low, high)
    delay(shortPressTime);
    xbeeCoordinator.print("Detect Drive Mode with Double Click!\n");
    if (digitalRead(button) == HIGH) {
        delay(shortPressTime * shortPressTime);
        if (digitalRead(button) == LOW) {
            delay(shortPressTime * ShortPressTime);
            if (digitalRead(button)==HIGH) {
                return(true);
            }
        }
    }
    return(false);
}

void DriveModeTransition() {
  RunMode = speechMode;
  bp (1);
  xbeeCoordinator.print("Drive Mode!\n");
  digitalWrite (speechCommPort,HIGH);
  digitalWrite (driveCommPort,LOW);
  delay (50);
  digitalWrite (speechCommPort,LOW);
  digitalWrite (driveModeLight,HIGH);
  digitalWrite (speechModeLight,LOW);
}
