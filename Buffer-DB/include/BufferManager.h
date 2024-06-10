#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

/*Erick Malcoaccha | Jose Paredes*/

#include <iostream>

#include "BufferPool.h"

class BufferManager {
   private:
    int numFrames;
    BufferPool bpool;

   public:
    // Constructor
    BufferManager(int numFrames);

    // Métodos
    void loadPageFromDisk(string blockPath, int pageID, char _mode);
    void killProcess(int pageID);
    void savePageToDisk(int pageID);
    void updatePage(int pageID);
    void deletePage(int pageID);
    void printTableFrame();
};

#endif  // BUFFERMANAGER_H
