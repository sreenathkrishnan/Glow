#pragma once

enum ButtonState {
    Active,
    Inactive,
};

enum ButtonEvent {
    None,
    ShortPress,
    LongPress
};

const unsigned long shortPressDuration = 100;
const unsigned long longPressDuration = 2000;

class Button {
    ButtonState state;
    uint8_t pin;
    ButtonEvent event;
    unsigned long startTime;

public:

    Button(uint8_t _pin);
    ButtonEvent getEvent();
};
