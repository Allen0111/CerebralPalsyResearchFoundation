



//LED transition flash sequence//
void modeTransitionIndicator(int pin){
  for (int i = 0; i < 9; i++) {
      xbeeCoordinator.print("LED FLASH\n");
      digitalWrite (x, HIGH);
      delay (300 - (sin(i * 0.146) * 290));
      digitalWrite (x, LOW);
      delay (300 - (sin (i * 0.146) * 300));
  }
  delay(600);
}
