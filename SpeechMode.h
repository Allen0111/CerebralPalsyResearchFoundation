/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: SpeechMode.h                                                         *
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


#ifndef SpeechMode_h

#define SpeechMode_h

    #include <math.h>  
    #include <SoftwareSerial.h>
    using namespace std;
      

    class SpeechMode {
  
        //private access
        private:
        
            //variables
            static int speechModeLightPin; 
            static int speechMode;
            static int speechCommPortPin;
            bool speechModeActive;
            int timer;
            int SensorVal;
            static const int longPressTime = 120;    //variable for long press (5 second default) 
                                                        //for possible potentiometer integration
            
            //functions    
            void incrementTimer();
            void timerReset();
            
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
            bool getSpeechStatus();     //returns true if Speech Mode if active, False if inactive
    
            //control functions        
            void scanForSpeechCompletion(int button);    //function that checks for the finish speech cue
            bool speechModeTransition();
    };
    
#endif
