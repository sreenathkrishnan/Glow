
#include "Particle.h"

class Lamp {

    uint8_t pin;
    bool state;

public:
    Lamp(uint8_t _pin) : pin(_pin) {
        pinMode(pin, OUTPUT);
        state = false;
        digitalWrite(pin, LOW);
    }

    void on() {
        state = true;
        digitalWrite(pin, HIGH);
    }

    void off() {
        state = false;
        digitalWrite(pin, LOW);
    }
};
