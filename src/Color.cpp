
#include "Particle.h"
#include "Color.h"


Color::Color() : r(0), g(0), b(0) {

}

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {

}

uint8_t Color::red() {
    return r;
}

uint8_t Color::blue() {
    return b;
}

uint8_t Color::green() {
    return g;
}

void Color::set(uint8_t _r, uint8_t _g, uint8_t _b) {
    r = _r;
    g = _g;
    b = _b;
}

uint32_t Color::pack() {
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint32_t Color::pack(float fraction) {
    fraction = max(fraction, 0.0);
    fraction = min(fraction, 1.0);
    return ((uint32_t)(r * fraction) << 16) | ((uint32_t)(g * fraction) <<  8) | (uint32_t)(b * fraction);
}
