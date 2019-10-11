#define DEBUG_SERIAL 0
#define NUM_LEDS 120
#define EEPROM_TIME 30000

// пины
#define PANEL_PIN 3
#define RGB_B 5
#define RGB_R 6
#define RGB_G 9
#define CEIL_PIN 10
#define TABLE_PIN 11
#define SOFT_1 4
#define SOFT_2 7
#define APA_DATA 12
#define APA_CLK 8
#define IR_PIN 2

#define LED_1 13
#define LED_2 14
#define LED_3 15
#define LED_4 16
#define LED_5 17
#define LED_6 18
#define LED_7 19

#if (DEBUG_SERIAL == 1)
#define DEBUG(x) Serial.println(x)
#else
#define DEBUG(x)  // удаляет вывод из кода
#endif

enum {
  TABLE_BRIGHT,
  CEIL_BRIGHT,
  RGB_H,
  RGB_S,
  RGB_V,
  APA_LEN,
  APA_H,
  APA_S,
  APA_V,
} controlSettings;

boolean apaSide;  // 0 - левая
const byte LEDpins[] = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};
const byte lightPins[] = {PANEL_PIN, SOFT_1, SOFT_2, TABLE_PIN, CEIL_PIN, RGB_B, RGB_R, RGB_G};
byte currentSet;
uint32_t blinkTimer;
boolean blinkFlag;

boolean eepromFlag;
uint32_t eepromTimer;

boolean states[7];
byte tableBright;
byte ceilBright;
struct {
  byte H;
  byte S;
  byte V;
} strip;
struct {
  byte length1;
  byte length2;
  byte H1;
  byte S1;
  byte V1;
  byte H2;
  byte S2;
  byte V2;
} apa;

// коррекция времени для х8
#define micros() (micros() >> 3)
#define millis() (millis() >> 3)
//#define delay(n) delay((n) << 3)
void fixDelay(uint32_t ms) {
  delay(ms << 3);
}

#include <IRLremote.h>
#include "IRcodes.h"
CHashIR IRLremote;
#include <FastLED.h>
CRGB leds[NUM_LEDS];
#include <EEPROM.h>
