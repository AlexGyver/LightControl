void checkEEPROM() {
  if (eepromFlag && millis() - eepromTimer >= EEPROM_TIME) {
    eepromFlag = false;
    for (byte i = 0; i < 7; i++) {
      EEPROM.put(i, states[i]);
    }
    EEPROM.put(10, strip);
    EEPROM.put(15, tableBright);
    EEPROM.put(16, ceilBright);
    EEPROM.put(20, apa);
  }
}
