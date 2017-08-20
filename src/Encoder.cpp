
#include "Particle.h"
#include "Encoder.h"

const uint8_t ENCODER_INCREMENT = 4;

Encoder::Encoder(uint8_t pin1, uint8_t pin2) {
    pin[0] = pin1;
    pin[1] = pin2;
    pinMode(pin1, INPUT_PULLUP);
    pinMode(pin2, INPUT_PULLUP);
    lastEncoded = 0;
    encoderValue = 0;
    //call updateEncoder() when any high/low changed seen
    //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
    attachInterrupt(pin1, updateEncoder, CHANGE);
    attachInterrupt(pin2, updateEncoder, CHANGE);
}

long Encoder::position() {
    return encoderValue/ENCODER_INCREMENT;
}

long Encoder::position(long range_min, long range_max, bool cycle) { // [min inclusive, max exclusive)
    long range_len = range_max - range_min;
    if (!cycle) {
        encoderValue = max(0, encoderValue);
        encoderValue = min((range_len-1)*ENCODER_INCREMENT, encoderValue);
    }
    return (position() % range_len + range_len) % range_len + range_min;
}

void Encoder::update() {

    int encoded = (pinReadFast(pin[0]) << 1) | pinReadFast(pin[1]); //converting the 2 pin value to single number
    int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

    lastEncoded = encoded; //store this value for next time
}

void Encoder::reset() {
    encoderValue = 0;
}
