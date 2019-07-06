#include <FastLED.h>

#define LED_PIN0    7
#define INPUT_PIN0  A0
#define NUM_LEDS    10

#define OFF         0
#define ON          15

#define DELAY       250

CRGB    leds0[NUM_LEDS];
int     min0 = 1023;
int     max0 = 0;


void setup() {
  Serial.begin(57200);

  FastLED.addLeds<WS2812, LED_PIN0, GRB>(leds0, NUM_LEDS);
}

void loop() {
  int value = analogRead(INPUT_PIN0);
  Serial.println(value);
  
  if (value < min0) min0 = value;
  if (value > max0) max0 = value;
  value = map(value, min0, max0, 1, NUM_LEDS);

  setUV(value);
  FastLED.show();
  delay(DELAY);

  /*for (int i = 0; i < NUM_LEDS; i++) {
    leds0[i] = CRGB(ON, ON, ON);
    FastLED.show();
    delay(DELAY);
    }

    for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds0[i] = CRGB(OFF, OFF, OFF);
    FastLED.show();
    delay(DELAY);
    }*/
}

void setUV(int nLeds) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds0[i] = CRGB(OFF, OFF, OFF);
  }

  for (int i = 0; i < nLeds; i++) {
    leds0[i] = CRGB(ON, ON, ON);
  }
}
