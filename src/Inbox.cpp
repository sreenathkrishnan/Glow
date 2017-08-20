
#include "Particle.h"
#include "Inbox.h"


Inbox::Inbox() {
    messages = {"I love you!",
                "It has been a great journey.",
                ".",
                ".",
                ".",
                ".",
                ".",
                ".",
                ".",
                ".",
                ".",
                "."};
    isUnread = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    msgNum = 0;
    addSlot = 1;
}


void Inbox::activate(uint8_t _msgNum) {

    if (_msgNum < MAX_MESSAGES) {
        msgNum = _msgNum;
    } else {
        msgNum = 0;
    }

}

char Inbox::getChar(uint16_t pos) {

    isUnread[msgNum] = false;
    if (pos < msgLen()) {
        return messages[msgNum].charAt(pos);
    }
    return ' ';

}

uint8_t Inbox::msgLen() {
    return messages[msgNum].length();
}

int Inbox::add(String msg) {

    messages[addSlot] = msg;
    isUnread[addSlot] = true;
    addSlot = addSlot%(MAX_MESSAGES-1) + 1;
    return int(addSlot);

}
