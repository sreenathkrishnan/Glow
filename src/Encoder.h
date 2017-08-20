#pragma once

void updateEncoder();

class Encoder {

    uint8_t pin[2];
    volatile int lastEncoded;
    volatile long long encoderValue;

public:

    Encoder(uint8_t pin1, uint8_t pin2);
    long position();
    long position(long range_min, long range_max, bool cycle = true); // [min inclusive, max exclusive)
    void update();
    void reset();
};
