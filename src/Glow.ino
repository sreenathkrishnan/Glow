SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

#include "Inbox.h"
#include <neopixel.h>
#include "Matrix.h"
#include "Ring.h"
#include "Color.h"
#include "Button.h"
#include "Encoder.h"

// TODO
// 1. Cleanup
// 2. Github
// 3. Welcome msg
// 4. Word by word mode
// 5. Persistence (save msgs)
// 6. Status LED

enum State {
    MsgSelect,
    MsgRead
};

//these pins can not be changed 2/3 are special pins
const uint8_t encoderPin1 = D2;
const uint8_t encoderPin2 = D3;

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


void init(State s) {
    switch(s) {
        case State::MsgSelect:
            matrix.reset();
            encoder.reset();
            break;
        case State::MsgRead:
            matrix.reset();
            encoder.reset();
            break;
    }
}

void process(State s) {
    switch(s) {
        case State::MsgSelect:
            ring.selectAndHighlight(encoder.position(0, 12), inbox.isUnread);
            matrix.reset();
            break;
        case State::MsgRead:
            unsigned int msgLen = inbox.msgLen();
            unsigned int msgPos = encoder.position(0, msgLen, false);
            matrix.say(inbox.get(), msgPos);
            ring.progressBar(msgPos, msgLen);
            break;
    }
}

State transition(State state) {
    switch(state) {
        case State::MsgSelect:
            inbox.activate(encoder.position(0, 12));
            encoder.reset();
            ring.clear();
            matrix.reset();
            init(State::MsgRead);
            return State::MsgRead;
            break;
        case State::MsgRead:
            matrix.reset();
            encoder.reset();
            init(State::MsgSelect);
            return State::MsgSelect;
            break;
    }
}


void setup() {
    WiFi.on();
    WiFi.connect();
    waitFor(WiFi.ready, 30000);

    if (WiFi.ready()) {
        Particle.connect();
        Particle.function("text", textReceived);
    }

    pinMode(ledBacklitPin, OUTPUT);
    digitalWrite(ledBacklitPin, HIGH);
    state = State::MsgSelect;
    init(state);
}

void loop() {
    if (Particle.connected()) Particle.process();

    switch(button.getEvent()) {
        case ButtonEvent::ShortPress:
            state = transition(state);
            break;
        case ButtonEvent::LongPress:
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
