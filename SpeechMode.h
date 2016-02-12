/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: SpeechMode.h
 * Author: Allen Bui                                                                  







 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


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
            void changeSpeechMode(bool onOff);        
            
            //accessor functions
            int getSpeechModeLightPin();
            int getSpeechCommPortPin();
            int getSpeechMode();
            bool getSpeechStatus();
    
            //control functions        
            void scanForSpeechCommand(int button);
    };
    
#endif
