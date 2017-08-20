#pragma once


class Color {

    uint8_t r, g, b;

public:

    Color();
    Color(uint8_t _r, uint8_t _g, uint8_t _b);
    uint8_t red();
    uint8_t blue();
    uint8_t green();
    void set(uint8_t _r, uint8_t _g, uint8_t _b);
    uint32_t pack();
    uint32_t pack(float fraction);

};
