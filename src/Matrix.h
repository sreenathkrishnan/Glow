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
    uint8_t charToPixel(char a);
    void sree();
    void malu();
    void love();
    void say(String msg, Color color);
    void twinkle(uint8_t pixel_num, Color color);

public:
    Matrix(uint8_t pin);
    void welcome();
    void init();
    void clear();
    void reset();
    void show(char a);
};
