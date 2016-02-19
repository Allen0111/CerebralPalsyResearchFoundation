/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: DriveMode.h                                                          *
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

#ifndef DriveMode_h

#define DriveMode_h

    #include <Arduino.h>
    #include <SoftwareSerial.h>
    #include <stdlib.h>
    #include <stdio.h> 
    using namespace std;

    class DriveMode {
  
        //private access variables 
        private:        
            const byte driveIdentification = 'a';
            const byte driveHigh = 'b';
            const byte driveLow = 'c';
            const byte driveVerification = 'D';

            int count = 0;
            int driveModeLightPin;
            int driveCommPortPin;
            int driveMode;
            static const int shortPressTime = 130;
            bool driveModeActive;
            int buttonPushCounter = 0;   // counter for the number of button presses
            int buttonState = 0;         // current state of the button
            int lastButtonState = 0;
        
        //public access functions
        public:

            // type constructor
            DriveMode();
    
            //deconstructor
            ~DriveMode();
    
            //accessor functions
            int getDriveModeLightPin();    //returns the GPIO port for the LED pin
            int getDriveCommPortPin();         //returns the GPIO comm port 
            int getDriveMode();            //returns the Idetification number of Drive Mode
            byte getDriveVerification();
            byte getDriveIdentification();
            bool getDriveStatus();     //returns true if Speech Mode if active, False if inactive
            
            //control functions
            bool scanForDriveCompletion(int button, SoftwareSerial *xbeeCoordinator);   //function to check for the drive cue
            bool timedEdgeDetection(int button);
            bool driveModeTransition(SoftwareSerial *xbeeCoordinator, char modeVerification, char modeIdentification);       //function to transition from some other mode, to drive mode. (ATTEMPTS TO OBTAIN THE SEMAPHORE KEY)
    };
    
#endif