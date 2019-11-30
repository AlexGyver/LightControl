void changeVal(byte value) {
  byte val8bit = (float)value * 13.4;
  DEBUG(val8bit);
  switch (controlSettings) {
    case TABLE_BRIGHT: tableBright = val8bit;
      break;
    case CEIL_BRIGHT: ceilBright = val8bit;
      break;
    case RGB_H: strip.H = val8bit;
      break;
    case RGB_S: strip.S = val8bit;
      break;
    case RGB_V: strip.V = val8bit;
      break;
    case APA_LEN:
      if (apaSide) {
        apa.length1 = (float)value * NUM_LEDS / 19;
      } else {
        apa.length2 = (float)value * NUM_LEDS / 19;
      }
      if (apa.length1 > NUM_LEDS - apa.length2)
        apa.length2 = NUM_LEDS - apa.length1;

      if (apa.length2 > NUM_LEDS - apa.length1)
        apa.length1 = NUM_LEDS - apa.length2;
      break;
    case APA_H:
      if (apaSide) {
        apa.H1 = val8bit;
      } else {
        apa.H2 = val8bit;
      }
      break;
    case APA_S:
      if (apaSide) {
        apa.S1 = val8bit;
      } else {
        apa.S2 = val8bit;
      }
      break;
    case APA_V:
      if (apaSide) {
        apa.V1 = val8bit;
      } else {
        apa.V2 = val8bit;
      }
      break;
  }
  switch (controlSettings) {
    case TABLE_BRIGHT:
      if (states[3]) {
        analogWriteCRT(TABLE_PIN, tableBright);
        blinkLED(3);
      }
      break;
    case CEIL_BRIGHT:
      if (states[4]) {
        analogWriteCRT(CEIL_PIN, ceilBright);
        blinkLED(4);
      }
      break;
    case RGB_H:
    case RGB_S:
    case RGB_V:
      switch (RGBmode) {
        case 0: RGBstrip.setHSV(strip.H, strip.S, strip.V);
          if (states[5]) RGBstrip.setBrightness(255);
          break;
        case 1:
          break;
        case 2:
          break;
      }
      blinkLED(5);
      break;
    case APA_LEN:
    case APA_H:
    case APA_S:
    case APA_V:
      if (states[6]) fillStrip();
      blinkLED(6);
      break;
  }
}
