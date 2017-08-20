
#include "Particle.h"
#include "Button.h"



Button::Button(uint8_t _pin) {
    pin = _pin;
    state = ButtonState::Inactive;
    event = ButtonEvent::None;
    pinMode(pin, INPUT);
}


ButtonEvent Button::getEvent() {

    if (digitalRead(pin) == LOW) { // not pressed
        if (state == ButtonState::Active) {
            state = ButtonState::Inactive;
            if ( (millis() - startTime) > longPressDuration ) {
                event = ButtonEvent::LongPress;
            } else if ( (millis() - startTime) > shortPressDuration ) {
                event = ButtonEvent::ShortPress;
            } else {
                event = ButtonEvent::None;
            }
        } else {
            event = ButtonEvent::None;
        }
    } else { // button pressed
        if (state == ButtonState::Inactive) {
            state = ButtonState::Active;
            startTime = millis();
        }
        event = ButtonEvent::None;
    }
    return event;

}
