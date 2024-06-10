#ifndef FRAME_H
#define FRAME_H

#include "Page.h"

class Frame {
   private:
    int frameID;
    bool dirty_flag;
    int pinCount;
    Page page;

   public:
    // Constructor
    Frame(int frameID);


    // Getters
    int getframeID();
    bool isDirty();
    int getPinCount();


    Page& getPage();

    // Setters
    void setFrameID(int id);
    void setDirtyFlag(bool dirty);
    void setPinCount(int pin);
    void setPage(Page pg);
    void incrementPinCount();
    void decrementPinCount();
};

#endif  // FRAME_H
