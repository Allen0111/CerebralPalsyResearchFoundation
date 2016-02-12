/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Document Name: SpeechMode
 * Author: Allen Bui                                                                  








 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



//no arg constructor
SpeechMode::SpeechMode() {
    speechModeLightPin = 9;
    speechMode = 0;
    speechCommPortPin = 5;
    speechModeActive = false;
    timer = resetTimer();
}

//deconstructor
SpeechMode::~SpeechMode() {
}


//mutator definition
void changeSpeechMode(boolean onOff) {
   speechModeActive = onOff; 
}

//accessor definitions
int getSpeechModeLightPin() {
    return speechModeLightPin;      
}
    
int getSpeechMode() {
    return speechMode;        
}      

int getSpeechCommPortPin() {
    return speechCommPortPin; 
}

boolean getSpeechStatus() {
    return speechModeActive;
}


void scanForSpeechCommand(int button) {    // detect speech mode by scanning for long press (5 second default)   
    
    clickDetector = digitalRead(button);
    
    xbeeCoordinator.print("Detect Talk Mode with long press!\n");
    
    for(clickDetector; clickDetector == LOW; clickDetector = digitalRead(button)) {
        incrementTimer();
        delay(20);
    }
    
    if (timer > longPressTime){
        resetTimer();
        Shift_Board_Mode ();
    }
}


void SpeechModeTransition() {
  current = driveMode;
  bp (2);
  xbeeCoordinator.print("Talk Mode!\n");
  digitalWrite (driveCommPort,HIGH);
  digitalWrite (speechCommPort,LOW);
  delay (50);
  digitalWrite (driveCommPort,LOW);
  digitalWrite (speechModeLight,HIGH);
  digitalWrite (driveModeLight,LOW);
}


void incrementTimer() {
    timer++;
}

void resetTimer() {
    timer = 0;
}
