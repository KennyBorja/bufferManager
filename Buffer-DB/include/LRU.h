#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <vector>
using namespace std;

class LRU {
 private:
  int size;
  vector<int> lru;

 public:
  LRU();
  LRU(int size_);
  void addPageIDtoLRU(int pageID);
  void deletePageIDfromLRU();
  int getLRUforDelete();
  void printLRU();
};

#endif