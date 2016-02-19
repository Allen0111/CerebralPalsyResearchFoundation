/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: LightControl.h                                                       *
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

#ifndef LightControl_h

#define LightControl_h

    #include <math.h>  
    #include <SoftwareSerial.h>
    using namespace std;

    class LightControl {
  
        //private access variables 
        private:
            int loopForTrue;
            int loopForTransition;
            enum mode {mode1 = 0, mode2};
            
        //public access functions
        public:

            // type constructor
            LightControl();
    
            //deconstructor
            ~LightControl();
        
            //mutator functions

    
            //accessor functions


            //control functions
            void selfCheckTrue(int lightPin);
            void modeTransitionIndicator(int goFromLightPin, int goToLightPin);
            void coordinatorStatusTrue(int coordinatorStatusLight);
    };
    
#endif
