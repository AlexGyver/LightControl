int rndVal;
float val;
byte fireBright;
uint32_t prevTime, prevTime2;
byte thisBrightness;
#define SMOOTH_K 0.2       // коэффициент плавности огня

void effectsTick() {
  if (RGBmode == 1 && states[5]) {
    if (millis() - prevTime > 100) {    // задаём направление яркости каждые 100 мс
      prevTime = millis();
      rndVal = random(0, 13);
    }
    if (millis() - prevTime2 > 20) {    // фильтрованная отрисовка каждые 20 мс
      prevTime2 = millis();
      val = (float)val * (1 - SMOOTH_K) + (float)rndVal * 10 * SMOOTH_K;
      thisBrightness = map(val, 0, 120, 100, 255);
      RGBstrip.colorWheel(strip.H * 6 + val * 0.6);
      RGBstrip.setBrightness(thisBrightness);
    }
  }
}

void controlAll(boolean state) {
  if (!state) {
    for (byte i = 0; i < 8; i++) {
      digitalWrite(lightPins[i], 0);
      FastLED.clear();
      FastLED.show();
    }
    for (byte i = 0; i < 7; i++) {
      digitalWrite(LEDpins[i], 0);
    }
  } else {
    digitalWrite(PANEL_PIN, states[0]);
    digitalWrite(SOFT_1, states[1]);
    digitalWrite(SOFT_2, states[2]);
    if (states[3]) analogWriteCRT(TABLE_PIN, tableBright);
    if (states[4]) analogWriteCRT(CEIL_PIN, ceilBright);
    if (states[5]) {
      switch (RGBmode) {
        case 0: RGBstrip.setHSV(strip.H, strip.S, strip.V);
          RGBstrip.setBrightness(255);
          break;
        case 1:
          break;
        case 2:
          break;
      }
    }
    if (states[6]) fillStrip();
    else {
      FastLED.clear();
      FastLED.show();
    }
    for (byte i = 0; i < 7; i++) {
      digitalWrite(LEDpins[i], states[i]);
    }
  }
}

// 0 - panel
// 1 - soft1
// 2 - soft2
// 3 - table
// 4 - ceil
// 5 - rgb
// 6 - apa

void fillStrip() {
  FastLED.clear();
  CHSV color = CHSV(apa.H1, apa.S1, apa.V1);
  for (byte i = 0; i < apa.length1; i++) {
    leds[i] = color;
  }
  color = CHSV(apa.H2, apa.S2, apa.V2);
  for (byte i = NUM_LEDS - apa.length2; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}
