#include "../include/Frame.h"

/* Jose Paredes */
// Constructor
Frame::Frame(int frameID)
    : frameID(frameID), dirty_flag(false), pinCount(0) {}

// Getter for frameID
int Frame::getframeID() {
    return frameID;
}

// Getter for page
Page& Frame::getPage() {
    return page;
}

// Setter for page
void Frame::setPage(Page page) {
    this->page = page;
}

// Getter for dirty flag
bool Frame::isDirty() {
    return dirty_flag;
}

// Setter for dirty flag
void Frame::setDirtyFlag(bool dirty_flag) {
    this->dirty_flag = dirty_flag;
}

// Getter for pinCount
int Frame::getPinCount() {
    return pinCount;
}

// Increment pinCount
void Frame::incrementPinCount() {
    pinCount++;
}

// Decrement pinCount
void Frame::decrementPinCount() {
    pinCount--;
}
