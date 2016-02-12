/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: DriveMode.h
 * Author: Allen Bui                                                                  







 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef DriveMode_h

#define DriveMode_h

    #include <math.h>  
    #include <SoftwareSerial.h>
    using namespace std;


    class DriveMode {
  
        //private access variables 
        private:
    
            static int driveModeLightPin;
            static int driveCommPortPin;
            static int driveMode;
            static const int shortPressTime = 150;
            bool driveModeActive;
        
        //public access functions
        public:

            // type constructor
            DriveMode();
    
            //deconstructor
            ~DriveMode();
        
            //mutator functions
            void changeDriveMode(bool onOff);
    
            //accessor functions
            int getDriveModeLightPin();
            int getDriveCommPortPin();
            int getDriveMode();
            bool getDriveStatus();
            
            //control functions
            bool scanForDriveCommand(int button);
            bool DriveModeTransition();
    };
    
#endif
