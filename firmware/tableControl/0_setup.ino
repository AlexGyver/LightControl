void setup() {
#if DEBUG_SERIAL == 1
  Serial.begin(9600);
#endif

  IRLremote.begin(IR_PIN);
  for (byte i = 3; i <= 19; i++) pinMode(i, OUTPUT);

  // Пины D3 и D11 - 31.4 кГц
  TCCR2B = 0b00000001; // x1
  TCCR2A = 0b00000001; // phase correct
  // Пины D9 и D10 - 31.4 кГц
  TCCR1A = 0b00000001; // 8bit
  TCCR1B = 0b00000001; // x1 phase correct
  // Пины D5 и D6 - 7.8 кГц
  TCCR0B = 0b00000010; // x8
  TCCR0A = 0b00000011; // fast pwm

  FastLED.addLeds<APA102, APA_DATA, APA_CLK, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS)/*.setCorrection( TypicalLEDStrip )*/;
  FastLED.show();

  if (EEPROM.read(1023 != 100)) {
    EEPROM.write(1023, 100);
    for (byte i = 0; i < 7; i++) {
      EEPROM.put(i, states[i]);
    }
    EEPROM.put(10, strip);
    EEPROM.put(15, tableBright);
    EEPROM.put(16, ceilBright);
    EEPROM.put(20, apa);
  } else {
    for (byte i = 0; i < 7; i++) {
      EEPROM.get(i, states[i]);
    }
    EEPROM.get(10, strip);
    EEPROM.get(15, tableBright);
    EEPROM.get(16, ceilBright);
    EEPROM.get(20, apa);
  }
  controlAll(true);
}
