
#include "Particle.h"
#include "Matrix.h"

const uint16_t TWINKLE_DELAY = 20;
const uint16_t WORD_DELAY = 1000;

Matrix::Matrix(uint8_t pin) : strip(Adafruit_NeoPixel(MATRIX_COUNT, pin, MATRIX_TYPE)) {
    textColor = Color(0, 255, 255);
    strip.begin();
    strip.setBrightness(20);
    reset();
}

void Matrix::init() {
    reset();
    startTime = millis();
}

void Matrix::clear() {
    for (uint8_t i = 0; i < strip.numPixels(); ++i) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
}

void Matrix::reset() {
    clear();
    strip.show();
}

uint8_t Matrix::charToPixel(char a) {
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

void Matrix::show(char a) {
    clear();
    float fraction = 2.0 * float((millis() - startTime) % TWINKLE_PERIOD) / float(TWINKLE_PERIOD);
    fraction = min(fraction, 2.0 - fraction);
    uint8_t pixel = charToPixel(a);
    strip.setPixelColor(pixel, textColor.pack(fraction));
    strip.show();
}


void Matrix::welcome() {
    Color white = Color(255, 255, 255);
    for (uint8_t i = 0; i < 3; ++i) {
        say("Glow!", white);
        delay(WORD_DELAY);
    }
    say("happy", textColor);
    delay(WORD_DELAY);
    say("second", textColor);
    delay(WORD_DELAY);
    malu();
    delay(WORD_DELAY);
    say("a", textColor);
    delay(WORD_DELAY);
    say("gift", textColor);
    delay(WORD_DELAY);
    say("from", textColor);
    delay(WORD_DELAY);
    sree();
    delay(WORD_DELAY);
    say("with", textColor);
    delay(WORD_DELAY);
    love();
    delay(WORD_DELAY);
    delay(WORD_DELAY);
}

void Matrix::twinkle(uint8_t pixel_num, Color color) {
    for (uint8_t i = 0; i < 250; i+=10) {
        strip.setPixelColor(pixel_num, color.pack(float(i)/250));
        strip.show();
        delay(TWINKLE_DELAY);
    }
    for (uint8_t i = 250; i > 0; i-=10) {
        strip.setPixelColor(pixel_num, color.pack(float(i)/250));
        strip.show();
        delay(TWINKLE_DELAY);
    }
    strip.setPixelColor(pixel_num, strip.Color(0, 0, 0));
    strip.show();
}


void Matrix::say(String msg, Color color) {
    for(int i = 0; i < msg.length(); ++i) {
        twinkle(charToPixel(msg[i]), color);
    }
}

void Matrix::malu() {
    for (uint8_t j = 7; j < 32; j+=8) {
        for (uint8_t i = 0; i < 250; i+=10) {
            strip.setPixelColor(j, strip.Color(i, 0, i));
            strip.show();
            delay(2*TWINKLE_DELAY);
        }
    }
}

void Matrix::sree() {
    for (uint8_t j = 0; j < 32; j+=8) {
        for (uint8_t i = 0; i < 250; i+=10) {
            strip.setPixelColor(j, strip.Color(i, 0, i));
            strip.show();
            delay(2*TWINKLE_DELAY);
        }
    }
}

void Matrix::love() {
    for (uint8_t j = 34; j < 38; j+=1) {
        for (uint8_t i = 0; i < 250; i+=10) {
            strip.setPixelColor(j, strip.Color(i, 0, 0));
            strip.show();
            delay(2*TWINKLE_DELAY);
        }
    }

}
