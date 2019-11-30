void blinkLED(byte number) {
  /*if (digitalRead(LEDpins[number])) digitalWrite(LEDpins[number], 0);
    else digitalWrite(LEDpins[number], 1);
    if (number > 2) {
    digitalWrite(LEDpins[currentSet], 0);
    currentSet = number;
    }
    blinkTimer = millis();
    blinkFlag = true;*/
  for (byte i = 0; i < 7; i++) {
    if (i != number) digitalWrite(LEDpins[i], states[i]);
  }
  if (digitalRead(LEDpins[number])) digitalWrite(LEDpins[number], 0);
  else digitalWrite(LEDpins[number], 1);
  blinkTimer = millis();
  blinkFlag = true;
}

void checkLEDs() {
  if (blinkFlag) {
    if (millis() - blinkTimer >= 200) {
      /*blinkTimer = millis();
        for (byte i = 0; i < 7; i++) digitalWrite(LEDpins[i], 0);
        if (currentSet > 2) digitalWrite(LEDpins[currentSet], 1);*/
      blinkFlag = false;
      for (byte i = 0; i < 7; i++) {
        digitalWrite(LEDpins[i], states[i]);
      }
    }
  }
}
