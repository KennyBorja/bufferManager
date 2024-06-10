#include "../include/Page.h"

#include <iostream>

Page::Page() : Size(0), Name(""), pageID(-1) {
}

Page::Page(int size, string name) : Size(size), Name(name) {
}

int Page::getSize() {
  return Size;
}

void Page::setSize(int size) {
  Size = size;
}

int Page::getPageId() {
  return this->pageID;
}

void Page::setPageId(int pageId) {
  this->pageID = pageId;
}

string Page::getName() {
  return Name;
}

void Page::setName(string name) {
  Name = name;
}

bool Page::addRecordInContent(string &record) {
  // Asumiendo que cada carácter cuenta como un byte
  int recordSize = record.size();
  if (recordSize <= Size) {
    content.push_back(record);
    Size -= recordSize; // Ajustar el tamaño restante
    return true;
  }
  return false;
}

bool Page::deleteRecordInContent(int index) {
  if (index >= 0 && index < content.size()) {
    Size += content[index].size(); // Recuperar el tamaño del registro eliminado
    content.erase(content.begin() + index);
    return true;
  }
  return false;
}

vector<string> &Page::getContent() {
  return content;
}
