#pragma once

#include "Particle.h"

class Status {

    uint8_t rPin, gPin, bPin;

public:

    Status(uint8_t rP, uint8_t gP, uint8_t bP) : rPin(rP), gPin(gP), bPin(bP) {
        pinMode(rPin, OUTPUT);
        pinMode(gPin, OUTPUT);
        pinMode(bPin, OUTPUT);
    }

    void set(bool r, bool g, bool b) {
        digitalWrite(rPin, r ? LOW:HIGH);
        digitalWrite(gPin, g ? LOW:HIGH);
        digitalWrite(bPin, b ? LOW:HIGH);
    }

    void red() {
        set(true, false, false);
    }

    void green() {
        set(false, true, false);
    }

    void blue() {
        set(false, false, true);
    }

    void yellow() {
        set(true, true, false);
    }

    void cyan() {
        set(false, true, true);
    }

    void purple() {
        set(true, false, true);
    }

    void white() {
        set(true, true, true);
    }

    void off() {
        set(false, false, false);
    }
};
