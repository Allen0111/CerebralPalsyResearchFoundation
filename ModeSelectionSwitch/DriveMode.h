
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
 * Document Name: DriveMode.h                                                          
 * Author: Allen Bui                                                                   
 * Last Revision : April 22, 2016                                                    
 * Revision No.: ---                                                                   
 * 
 * DriveMode encapsulates all of the variables and functions that act as a drive 
 * mechanism.                                                       
 *
 */

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
            const int wishToTransitionCount = 3;        // number of button presses before transition

            int count = 0;
            int driveModeLightPin;
            int driveCommPortPin;
            int driveMode;
            static const int shortPressTime = 130;
            bool driveModeActive;
            int buttonPushCounter = 0;   // counter for the number of button presses
            int buttonState = 0;         // current state of the button
            int lastButtonState = 0;
            unsigned long long timer;
            
            int allottedTime = 1200;    //two seconds

            bool timedEdgeDetection(int button);

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
            bool driveModeTransition(SoftwareSerial *xbeeCoordinator, char modeVerification, char modeIdentification);       //function to transition from some other mode, to drive mode. (ATTEMPTS TO OBTAIN THE SEMAPHORE KEY)
            void resetTimer();
            void incrementButton();
    };
    
#endif
