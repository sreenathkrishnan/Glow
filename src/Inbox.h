#pragma once

const uint8_t MAX_MESSAGES = 12;

class Inbox {
    std::array<String, MAX_MESSAGES> messages;
    uint8_t msgNum;
    uint8_t addSlot;

public:
    std::array<bool, MAX_MESSAGES>  isUnread;

    Inbox();
    void activate(uint8_t _msgNum);
    char getChar(uint16_t pos);
    uint8_t msgLen();
    int add(String msg);

};
