#pragma once
#include <iostream>

template <class X> class PriorityQueue {
private:
  X *data;
  int maxSize;
  int currentSize;

public:
  PriorityQueue();
  ~PriorityQueue();
  bool enQueue(X key);
  bool deQueue(X &key);
  void show();
};

template <class X> PriorityQueue<X>::PriorityQueue() {
  data = new X[10];
  maxSize = 10;
  currentSize = 0;
}

template <class X> PriorityQueue<X>::~PriorityQueue() { delete[] data; }

template <class X> bool PriorityQueue<X>::enQueue(X key) {
  if (maxSize == currentSize) { // if queue is full
    std::cout << "Not enough space. Requesting more..." << std::endl;
    X *temp;
    temp = new X[maxSize + 5];
    if (temp != NULL) {
      std::cout << "Space found. Moving data..." << std::endl;
      for (int i = 0; i < maxSize; i++) {
        temp[i] = data[i];
      }
      delete[] data;
      data = temp;
      maxSize += 5;
    } else {
      std::cout << "Space not found. Stopping." << std::endl;
      return false;
    }
  }

  if (currentSize == 0) { // if list is empty
    data[0] = key;
    currentSize++;
    return true;
  }

  bool gotIn = false;  // if list is not empty   
  for (int i = 0; i < currentSize && !gotIn; i++) {
    if (key > data[i]) {
      gotIn = true;
      for (int j = currentSize-1; j >= i; j--) {
        data[j + 1] = data[j];
      }
      data[i] = key;
      currentSize++;
    }
  }
  if (!gotIn) { // if key is smaller than all elements
    data[currentSize++] = key;
  }
  return true;
};

template <class X> bool PriorityQueue<X>::deQueue(X &key) {
  if (currentSize == 0) {
    std::cout << "Array empty..." << std::endl;
    return false;
  }
  key = data[0];
  for (int i = 0; i < currentSize - 1; i++) {
    data[i] = data[i + 1];
  }
  currentSize--;
  if (maxSize - currentSize >= 5) {
    X *temp;
    temp = new X[maxSize - 5];
    if (temp != NULL) {
      std::cout << "Too much available space. Deleting extra memory..." << std::endl;
      for (int i = 0; i < currentSize; i++) {
        temp[i] = data[i];
      }
      delete[] data;
      data = temp;
      maxSize -= 5;
      std::cout << "Extra space deleted." << std::endl;
    } else {
      std::cout << "Could not delete extra space." << std::endl;
      return false;
    }
  }
  return true;
}

template <class X> void PriorityQueue<X>::show() {
  std::cout << "--------------" << std::endl;
  std::cout << "Size = " << currentSize << std::endl;
  std::cout << "maxSize = " << maxSize << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << std::endl;
  }
  std::cout << "--------------" << std::endl;
};