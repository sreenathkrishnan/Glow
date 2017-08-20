#pragma once

const uint8_t MAX_MESSAGES = 12;

class Inbox {
    std::array<String, MAX_MESSAGES> messages;
    uint8_t msgNum;
    uint8_t addSlot;

public:
    std::array<bool, MAX_MESSAGES>  isUnread;

    Inbox() {
        messages = {"I love you!", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
        isUnread = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        msgNum = 0;
        addSlot = 1;
    }


    void activate(uint8_t _msgNum) {
        if (_msgNum < MAX_MESSAGES) {
            msgNum = _msgNum;
        } else {
            msgNum = 0;
        }
    }

    String get() {
        if (msgNum < MAX_MESSAGES) {
            isUnread[msgNum] = false;
            return messages[msgNum];
        }
        return "";
    }

    uint8_t msgLen() {
        return messages[msgNum].length();
    }

    int add(String msg) {
        messages[addSlot] = msg;
        isUnread[addSlot] = true;
        addSlot = addSlot%(MAX_MESSAGES-1) + 1;
        return int(addSlot);
    }

};
