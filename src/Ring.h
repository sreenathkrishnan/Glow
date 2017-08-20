#pragma once

#include <neopixel.h>
#include "Color.h"

#define RING_COUNT 12
#define RING_TYPE WS2812B


const uint8_t ringZeroOffset = 4;
class Ring {
    Adafruit_NeoPixel strip;
    Color progressColor;
    Color highlightColor;
    Color selectColor;

public:
    Ring(uint8_t pin) : strip(Adafruit_NeoPixel(RING_COUNT, pin, RING_TYPE)) {
        progressColor = Color(255, 0, 204);
        highlightColor = Color(0, 255, 0);
        selectColor = Color(51, 102, 255);
        strip.begin();
        strip.setBrightness(5);
        clear();
    }

    uint8_t getPixel(uint8_t num) {
        return (num + ringZeroOffset) % strip.numPixels();
    }

    void progressBar(uint8_t num) {
        for (uint8_t i = 0; i < strip.numPixels(); ++i) {
            uint8_t pixel = (i + ringZeroOffset) % strip.numPixels();
            if (i <= num) {
                strip.setPixelColor(pixel, progressColor.pack());
            } else {
                strip.setPixelColor(pixel, strip.Color(0, 0, 0));
            }
        }
        strip.show();
    }

    void progressBar(unsigned int pos, unsigned int maxPos) {
        progressBar(((pos+1)*strip.numPixels())/maxPos);
    }

    void select(uint8_t select_pixel) {
        for (uint8_t i = 0; i < strip.numPixels(); ++i) {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
        strip.setPixelColor(getPixel(select_pixel), selectColor.pack());
        strip.show();
    }

    void selectAndHighlight(uint8_t select_pixel, std::array<bool, RING_COUNT> isHigh) {
        for (uint8_t i = 0; i < strip.numPixels(); ++i) {
            uint8_t pixel = getPixel(i);
            if (isHigh[i]) {
                strip.setPixelColor(pixel, highlightColor.pack());
            } else {
                strip.setPixelColor(pixel, strip.Color(0, 0, 0));
            }
        }
        strip.setPixelColor(getPixel(select_pixel), selectColor.pack());
        strip.show();
    }

    void clear() {
        for (uint8_t i = 0; i < strip.numPixels(); ++i) {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
    }

};
