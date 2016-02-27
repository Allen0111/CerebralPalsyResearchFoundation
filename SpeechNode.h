// Author: Jerek Shoemaker
// Last Revision: February 26 2016
// SpeechNode.h

#ifndef SpeechNode_h

#define SpeechNode_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
 
using namespace std;

class SpeechNode {
    private:
        const static int output = 4;
        char letter;
        bool active;

    public:
        // Constructor
        SpeechNode();
        
        // Deconstructor
        ~SpeechNode();

        // Getters
        byte getLetter();
        bool isActive();

        // Setters
        void activate();
        void deactivate();
        void on();
        void off();
        void setLetter(byte l);
};

#endif
