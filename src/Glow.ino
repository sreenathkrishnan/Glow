SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

#include "Inbox.h"
#include <neopixel.h>
#include "Matrix.h"
#include "Ring.h"
#include "Color.h"
#include "Button.h"
#include "Encoder.h"
#include "Status.h"
#include "Lamp.h"

// TODO
// 1. Cleanup
// 3. Welcome msg
// 4. Word by word mode
// 5. Persistence (save msgs)
// 7. SLeep mode

enum State {
    MsgSelect,
    MsgRead,
    NightLamp
};

//these pins can not be changed 2/3 are special pins
const uint8_t encoderPin1 = D2;
const uint8_t encoderPin2 = D3;
const uint8_t encoderRedPin = A5;
const uint8_t encoderGreenPin = D4;
const uint8_t encoderBluePin = D5;

const uint8_t buttonPin = A4;
const uint8_t ringPin = D6;
const uint8_t matrixPin = D7;
const uint8_t ledBacklitPin = A0;

Encoder encoder(encoderPin1, encoderPin2);
Ring ring(ringPin);
Matrix matrix(matrixPin);
Button button(buttonPin);
State state;
Inbox inbox;
Status status(encoderRedPin, encoderGreenPin, encoderBluePin);
Lamp lamp(ledBacklitPin);

void init(State s) {
    encoder.reset();
    ring.reset();
    matrix.reset();
    switch(s) {
        case State::MsgSelect:
            break;
        case State::MsgRead:
            break;
        case State::NightLamp:
            lamp.on();
            status.off();
            break;
    }
}

void process(State s) {
    switch(s) {
        case State::MsgSelect: {
            ring.selectAndHighlight(encoder.position(0, 12), inbox.isUnread);
            matrix.reset();
        } break;
        case State::MsgRead: {
            unsigned int msgLen = inbox.msgLen();
            unsigned int msgPos = encoder.position(0, msgLen, false);
            matrix.show(inbox.getChar(msgPos));
            ring.progressBar(msgPos, msgLen);
        } break;
        case State::NightLamp:
            status.off();
            break;
    }
}

State transition(State state) {
    switch(state) {
        case State::MsgSelect:
            inbox.activate(encoder.position(0, 12));
            init(State::MsgRead);
            return State::MsgRead;
            break;

        case State::MsgRead:
            init(State::NightLamp);
            return State::NightLamp;
            break;

        case State::NightLamp:
            lamp.off();
            init(State::MsgSelect);
            return State::MsgSelect;
            break;
    }
}


void setup() {
    status.blue();
    ring.reset();
    matrix.welcome();

    WiFi.on();
    WiFi.connect();
    waitFor(WiFi.ready, 30000);

    if (WiFi.ready()) {
        Particle.connect();
        Particle.function("text", textReceived);
        status.cyan();
    } else {
        status.white();
    }

    state = State::MsgSelect;
    init(state);
}

void loop() {
    if (Particle.connected()) {
        if(state != State::NightLamp) status.cyan();
        Particle.process();
    } else {
        if(state != State::NightLamp) status.white();
    }

    switch(button.getEvent()) {
        case ButtonEvent::ShortPress:
            state = transition(state);
            break;
        case ButtonEvent::LongPress:
            status.green();
            WiFi.listen();
            break;
    }
    process(state);
}

void updateEncoder(){
    encoder.update();
}


int textReceived(String command) {
    return inbox.add(command);
}
