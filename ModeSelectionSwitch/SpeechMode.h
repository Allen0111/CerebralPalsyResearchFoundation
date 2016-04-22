
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
 * Document Name: SpeechMode.h                                                         
 * Author: Allen Bui                                                                   
 * Last Revision : April 22, 2016                                                    
 * Revision No.: ---                                                                   
 *                                                                                     
 * SpeechMode encapsulates all of the variables and functions that act as a speech mechanism                                                      
 */

#ifndef SpeechMode_h

#define SpeechMode_h

    #include <Arduino.h>
    #include <SoftwareSerial.h>
    #include <stdlib.h>
    #include <stdio.h> 
    using namespace std;
      

    class SpeechMode {
  
        //private access
        private:
                      // variables
            const byte speechIdentification = 'x';
            const byte speechHigh = 'y';
            const byte speechLow = 'z';
            const byte speechVerification = 'T';

            int speechModeLightPin; 
            int speechMode;
            int speechCommPortPin;
            bool speechModeActive;
            bool firstClick;
            int timer;
            int SensorVal;
            static const int longPressTime = 80;    //variable for long press (5 second default) 
                                                        //for possible potentiometer integration
                      //member functions    
            void incrementTimer();
            void resetTimer();
            
        //public access
        public:
        
            // type constructor
            SpeechMode();
        
            //deconstructor
            ~SpeechMode();
            
            //mutator functions
            void changeSpeechMode(bool onOff);        //Modify the speech mode Active/Inactive variable
            
            //accessor functions
            int getSpeechModeLightPin();    //returns the GPIO port for the LED pin
            int getSpeechCommPortPin();         //returns the GPIO comm port 
            int getSpeechMode();            //returns the Idetification number of Speech Mode
            byte getSpeechVerification();
            byte getSpeechIdentification();
            bool getSpeechStatus();     //returns true if Speech Mode if active, False if inactive
    
            //control functions        
            bool scanForSpeechCompletion(int button, SoftwareSerial *xbeeCoordinator);    //function that checks for the finish speech cue
            bool speechModeTransition(SoftwareSerial *xbeeCoordinator, char modeVerification, char modeIdentification);
            void setFirstClick();
    };
    
#endif
