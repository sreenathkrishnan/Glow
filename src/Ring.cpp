
#include "Particle.h"
#include "Ring.h"


Ring::Ring(uint8_t pin) : strip(Adafruit_NeoPixel(RING_COUNT, pin, RING_TYPE)) {
    highlightColor = Color(255, 0, 204);
    progressColor = Color(0, 255, 0);
    selectColor = Color(51, 102, 255);
    strip.begin();
    strip.setBrightness(5);
    clear();
}

uint8_t Ring::getPixel(uint8_t num) {
    return (num + ringZeroOffset) % strip.numPixels();
}

void Ring::progressBar(uint8_t num) {
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

void Ring::progressBar(unsigned int pos, unsigned int maxPos) {
    progressBar(((pos+1)*strip.numPixels())/maxPos);
}

void Ring::selectAndHighlight(uint8_t select_pixel, std::array<bool, RING_COUNT> isHigh) {
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

void Ring::clear() {
    for (uint8_t i = 0; i < strip.numPixels(); ++i) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
}

void Ring::reset() {
    clear();
    strip.show();
}
