// Author: Jerek Shoemaker
// Latest Revision: October 9, 2015

#include <SoftwareSerial.h>
char letter = '0';
char words[20];
int index = 0;
int led1 = 10;
int led2 = 11;
SoftwareSerial bee(2, 3);

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  Serial.begin(9600);
  bee.begin(9600);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  Serial.println("Ready");
}

void loop() { // run over and over
  while(bee.available() > 0)
  {
    letter = bee.read();
    if(letter != '\n' && letter != ' ' && letter != '\r')
    {
      letter = tolower(letter);
      words[index] = letter;
      index++;
      words[index] = '\0';
    }
    else
    {
      words[index] = '\0';
      index = 0;
      if(strcmp(words, "talk") == 0)
      {
        Serial.println("Command Accepted");
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
      }
      if(strcmp(words, "drive") == 0)
      {
        Serial.println("Command Rejected");
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
      }
    }
  }
  words[index] = '\0';
  if(strcmp(words, "drive") == 0)
  {
    Serial.println("Command Accepted");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  if(strcmp(words, "talk") == 0)
  {
    Serial.println("Command Rejected");
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  index = 0;
}
