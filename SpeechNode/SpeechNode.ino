// Author: Jerek Shoemaker
// Latest Revision: February 26 2015
// SpeechNode.ino

#include <Arduino.h>
#include "SpeechNode.h"

SpeechNode::SpeechNode() 
{
    letter = '0';
    active = false;
    pinMode(output, OUTPUT);
}

SpeechNode::~SpeechNode() 
{
  // Nothing here
}

// GETTERS
byte SpeechNode::getLetter() 
{
    return letter;
}

bool SpeechNode::isActive() 
{
    return active;
}

// SETTERS
void SpeechNode::activate()
{
    active = true;
}

void SpeechNode::deactivate()
{
    active = false;
}

void SpeechNode::setLetter(byte l) 
{
    letter = l;
}

void SpeechNode::on() 
{
    digitalWrite(output, HIGH);
}

void SpeechNode::off()
{
    digitalWrite(output, LOW);
}
