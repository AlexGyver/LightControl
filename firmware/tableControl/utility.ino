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
    if (states[3]) analogWrite(TABLE_PIN, tableBright);
    if (states[4]) analogWrite(CEIL_PIN, ceilBright);
    if (states[5]) setHSV();
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

void setHSV() {
  float r, g, b;

  float H = (float)strip.H / 255;
  float S = (float)strip.S / 255;
  float V = (float)strip.V / 255;

  int i = int(H * 6);
  float f = H * 6 - i;
  float p = V * (1 - S);
  float q = V * (1 - f * S);
  float t = V * (1 - (1 - f) * S);

  switch (i % 6) {
    case 0: r = V, g = t, b = p; break;
    case 1: r = q, g = V, b = p; break;
    case 2: r = p, g = V, b = t; break;
    case 3: r = p, g = q, b = V; break;
    case 4: r = t, g = p, b = V; break;
    case 5: r = V, g = p, b = q; break;
  }
  r = r * 255;
  g = g * 255;
  b = b * 255;
  analogWrite(RGB_R, r);
  analogWrite(RGB_G, g);
  analogWrite(RGB_B, b);
}
