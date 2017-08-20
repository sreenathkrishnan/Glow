#pragma once
#include <neopixel.h>
#include "Color.h"

#define MATRIX_COUNT 40
#define MATRIX_TYPE WS2812B
const uint16_t TWINKLE_PERIOD = 1000;

class Matrix {
    Adafruit_NeoPixel strip;
    Color textColor;
    unsigned long startTime;

public:
    Matrix(uint8_t pin) : strip(Adafruit_NeoPixel(MATRIX_COUNT, pin, MATRIX_TYPE)) {
        textColor = Color(0, 255, 255);
        strip.begin();
        strip.setBrightness(20);
        reset();
    }

    void init() {
        clear();
        startTime = millis();
    }

    void clear() {
        for (uint8_t i = 0; i < strip.numPixels(); ++i) {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
    }

    void reset() {
        clear();
        strip.show();
    }

    uint8_t charToPixel(char a) {
        a = tolower(a);
        if (a == 'z') {
            return 38;
        } else if (a == '.') {
            return 32;
        } else if (a == '!') {
            return 39;
        } else {
            uint8_t row = int(a - 'a') / 6;
            uint8_t col = 1 + int(a - 'a')%6;
            return row*8 + col;
        }
    }

    void say(String msg, uint16_t pos) {
        clear();
        if (pos < msg.length()) {
            float fraction = 2.0 * float((millis() - startTime) % TWINKLE_PERIOD) / float(TWINKLE_PERIOD);
            fraction = min(fraction, 2.0 - fraction);
            uint8_t pixel = charToPixel(msg.charAt(pos));
            strip.setPixelColor(pixel, textColor.pack(fraction));
            strip.show();
        }
    }
};
