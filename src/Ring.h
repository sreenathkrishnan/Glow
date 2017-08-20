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
    uint8_t getPixel(uint8_t num);

public:
    Ring(uint8_t pin);

    void progressBar(uint8_t num);

    void progressBar(unsigned int pos, unsigned int maxPos);

    void selectAndHighlight(uint8_t select_pixel, std::array<bool, RING_COUNT> isHigh);

    void clear();

    void reset();

};
