/*
  Версия 1.1:
  - Яркость меняется по CRT гамме
  - Добавлен эффект огня (включается при повторном клике на RGB H)
  - Исправлены баги в управлении
*/

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
byte RGBmode = 0;   // 0 - цвет, 1 - огонь

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

#include <GyverRGB.h>
GRGB RGBstrip(RGB_R, RGB_G, RGB_B);  // куда подключены цвета (R, G, B)
#include <IRLremote.h>
#include "IRcodes.h"
CHashIR IRLremote;
#include <FastLED.h>
CRGB leds[NUM_LEDS];
#include <EEPROM.h>

const uint8_t CRT_gamma[256] PROGMEM = {
  0,    0,    1,    1,    1,    1,    1,    1,
  1,    1,    1,    1,    1,    1,    1,    1,
  2,    2,    2,    2,    2,    2,    2,    2,
  3,    3,    3,    3,    3,    3,    4,    4,
  4,    4,    4,    5,    5,    5,    5,    6,
  6,    6,    7,    7,    7,    8,    8,    8,
  9,    9,    9,    10,   10,   10,   11,   11,
  12,   12,   12,   13,   13,   14,   14,   15,
  15,   16,   16,   17,   17,   18,   18,   19,
  19,   20,   20,   21,   22,   22,   23,   23,
  24,   25,   25,   26,   26,   27,   28,   28,
  29,   30,   30,   31,   32,   33,   33,   34,
  35,   35,   36,   37,   38,   39,   39,   40,
  41,   42,   43,   43,   44,   45,   46,   47,
  48,   49,   49,   50,   51,   52,   53,   54,
  55,   56,   57,   58,   59,   60,   61,   62,
  63,   64,   65,   66,   67,   68,   69,   70,
  71,   72,   73,   74,   75,   76,   77,   79,
  80,   81,   82,   83,   84,   85,   87,   88,
  89,   90,   91,   93,   94,   95,   96,   98,
  99,   100,  101,  103,  104,  105,  107,  108,
  109,  110,  112,  113,  115,  116,  117,  119,
  120,  121,  123,  124,  126,  127,  129,  130,
  131,  133,  134,  136,  137,  139,  140,  142,
  143,  145,  146,  148,  149,  151,  153,  154,
  156,  157,  159,  161,  162,  164,  165,  167,
  169,  170,  172,  174,  175,  177,  179,  180,
  182,  184,  186,  187,  189,  191,  193,  194,
  196,  198,  200,  202,  203,  205,  207,  209,
  211,  213,  214,  216,  218,  220,  222,  224,
  226,  228,  230,  232,  233,  235,  237,  239,
  241,  243,  245,  247,  249,  251,  253,  255,
};

void analogWriteCRT(byte pin, byte val) {
  analogWrite(pin, pgm_read_byte(&(CRT_gamma[val])));
}
