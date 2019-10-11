void checkIR() {
  if (IRLremote.available()) {
    eepromFlag = true;
    eepromTimer = millis();
    auto data = IRLremote.read();
    switch (data.command) {

      // всё вкл
      case BUTT0: DEBUG(0);
        controlAll(true);
        break;

      // всё выкл
      case BUTT1: DEBUG(1);
        controlAll(false);
        break;

      // панель вкл
      case BUTT2: DEBUG(2);
        states[0] = true;
        digitalWrite(PANEL_PIN, states[0]);
        blinkLED(0);
        break;

      // панель выкл
      case BUTT3: DEBUG(3);
        states[0] = false;
        digitalWrite(PANEL_PIN, states[0]);
        blinkLED(0);
        break;

      // софт1 вкл
      case BUTT4: DEBUG(4);
        states[1] = true;
        digitalWrite(SOFT_1, states[1]);
        blinkLED(1);
        break;

      // софт 1 выкл
      case BUTT5: DEBUG(5);
        states[1] = false;
        digitalWrite(SOFT_1, states[1]);
        blinkLED(1);
        break;

      // софт2 вкл
      case BUTT6: DEBUG(6);
        states[2] = true;
        digitalWrite(SOFT_2, states[2]);
        blinkLED(2);
        break;

      // софт 2 выкл
      case BUTT7: DEBUG(7);
        states[2] = false;
        digitalWrite(SOFT_2, states[2]);
        blinkLED(2);
        break;

      // стол тоггл
      case BUTT8: DEBUG(8);
        states[3] = !states[3];
        if (states[3]) analogWrite(TABLE_PIN, tableBright);
        else digitalWrite(TABLE_PIN, 0);
        blinkLED(3);
        break;

      // стол яркость
      case BUTT9: DEBUG(9);
        controlSettings = TABLE_BRIGHT;
        blinkLED(3);
        break;

      // потолок тоггл
      case BUTT10: DEBUG(10);
        states[4] = !states[4];
        if (states[4]) analogWrite(CEIL_PIN, ceilBright);
        else digitalWrite(CEIL_PIN, 0);
        blinkLED(4);
        break;

      // потолок яркость
      case BUTT11: DEBUG(11);
        controlSettings = CEIL_BRIGHT;
        blinkLED(4);
        break;

      // rgb тоггл
      case BUTT12: DEBUG(12);
        states[5] = !states[5];
        if (states[5]) setHSV();
        else {
          digitalWrite(RGB_R, 0);
          digitalWrite(RGB_G, 0);
          digitalWrite(RGB_B, 0);
        }
        blinkLED(5);
        break;

      // H
      case BUTT13: DEBUG(13);
        controlSettings = RGB_H;
        blinkLED(5);
        break;

      // S
      case BUTT14: DEBUG(14);
        controlSettings = RGB_S;
        blinkLED(5);
        break;

      // V
      case BUTT15: DEBUG(15);
        controlSettings = RGB_V;
        blinkLED(5);
        break;

      // контр вкл
      case BUTT16: DEBUG(16);
        states[6] = true;
        fillStrip();
        blinkLED(6);
        break;

      // контр выкл
      case BUTT17: DEBUG(17);
        states[6] = false;
        FastLED.clear();
        FastLED.show();
        blinkLED(6);
        break;

      // левый
      case BUTT18: DEBUG(18);
        apaSide = true;
        blinkLED(6);
        break;

      // правый
      case BUTT19: DEBUG(19);
        apaSide = false;
        blinkLED(6);
        break;

      // длина 1
      case BUTT20: DEBUG(20);
        controlSettings = APA_LEN;
        blinkLED(6);
        break;

      // H
      case BUTT21: DEBUG(21);
        controlSettings = APA_H;
        blinkLED(6);
        break;

      // S
      case BUTT22: DEBUG(22);
        controlSettings = APA_S;
        blinkLED(6);
        break;

      // V
      case BUTT23: DEBUG(23);
        controlSettings = APA_V;
        blinkLED(6);
        break;

      // цифры
      case BUTT24: DEBUG(24);
        changeVal(0);
        break;
      case BUTT25: DEBUG(25);
        changeVal(1);
        break;
      case BUTT26: DEBUG(26);
        changeVal(2);
        break;
      case BUTT27: DEBUG(27);
        changeVal(3);
        break;
      case BUTT28: DEBUG(28);
        changeVal(4);
        break;
      case BUTT29: DEBUG(29);
        changeVal(5);
        break;
      case BUTT30: DEBUG(30);
        changeVal(6);
        break;
      case BUTT31: DEBUG(31);
        changeVal(7);
        break;
      case BUTT32: DEBUG(32);
        changeVal(8);
        break;
      case BUTT33: DEBUG(33);
        changeVal(9);
        break;
      case BUTT34: DEBUG(34);
        changeVal(10);
        break;
      case BUTT35: DEBUG(35);
        changeVal(11);
        break;
      case BUTT36: DEBUG(36);
        changeVal(12);
        break;
      case BUTT37: DEBUG(37);
        changeVal(13);
        break;
      case BUTT38: DEBUG(38);
        changeVal(14);
        break;
      case BUTT39: DEBUG(39);
        changeVal(15);
        break;
      case BUTT40: DEBUG(40);
        changeVal(16);
        break;
      case BUTT41: DEBUG(41);
        changeVal(17);
        break;
      case BUTT42: DEBUG(42);
        changeVal(18);
        break;
      case BUTT43: DEBUG(43);
        changeVal(19);
        break;
    }
  }
}
