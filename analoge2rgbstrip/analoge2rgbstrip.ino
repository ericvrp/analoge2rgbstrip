#include <FastLED.h>

#define FALSE       0
#define TRUE        1

#define DEBUG       FALSE

#define LEDSTRIP_BASE_PIN       7   // 2nd strip at base pin +1, etc.
#define ANALOG_INPUT_BASE_PIN   A0  // 2nd strip at base pin +1, etc.
#define N_STRIPS                4   // 4 seemed like a reasonable maximum amount (at some point)
#define NUM_LEDS_PER_STRIP      30

#define VALUE_OFFSET 10 // pretend we have measured this much more to prefend a flickering last led

#define OFF         0
#define ON          15

#define DELAY       100

CRGB    leds[N_STRIPS][NUM_LEDS_PER_STRIP];
int     min0[N_STRIPS];
int     max0[N_STRIPS];


void setup() {
#if DEBUG
  Serial.begin(57600);
#endif

  for (int strip = 0; strip < N_STRIPS; strip++) {
    int ledStripPin = LEDSTRIP_BASE_PIN + strip;

    switch (ledStripPin) {
      //      case 0: FastLED.addLeds<WS2812, 0, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      //      case 1: FastLED.addLeds<WS2812, 1, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      //      case 2: FastLED.addLeds<WS2812, 2, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      //      case 3: FastLED.addLeds<WS2812, 3, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      //      case 4: FastLED.addLeds<WS2812, 4, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      //      case 5: FastLED.addLeds<WS2812, 5, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      //      case 6: FastLED.addLeds<WS2812, 6, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      case 7: FastLED.addLeds<WS2812, 7, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      case 8: FastLED.addLeds<WS2812, 8, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      case 9: FastLED.addLeds<WS2812, 9, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
      case 10: FastLED.addLeds<WS2812, 10, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
        //      case 11: FastLED.addLeds<WS2812, 11, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
        //      case 12: FastLED.addLeds<WS2812, 12, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
        //      case 13: FastLED.addLeds<WS2812, 13, GRB>(leds[strip], NUM_LEDS_PER_STRIP); break;
        // default: use at your own risc
    }

    int analogInputPin = ANALOG_INPUT_BASE_PIN + strip;
    min0[strip] = max0[strip] = analogRead(analogInputPin);
  }
}

void loop() {
  for (int strip = 0; strip < N_STRIPS; strip++) {
    int analogInputPin = ANALOG_INPUT_BASE_PIN + strip;
    int value = analogRead(analogInputPin);

#if DEBUG
    Serial.println(value);
#endif

    if (value < min0[strip]) min0[strip] = value;
    if (value > max0[strip]) max0[strip] = value;
    value = map(value + VALUE_OFFSET, min0[strip], max0[strip], 1, NUM_LEDS_PER_STRIP);

    setLeds(strip, value);
  } // next strip

  FastLED.show();
  delay(DELAY);
}

void setLeds(int strip, int nLeds) {
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    leds[strip][i] = CRGB(OFF, OFF, OFF);
  }

  for (int i = 0; i < nLeds; i++) {
    leds[strip][i] = CRGB(ON, ON, ON);
  }
}
