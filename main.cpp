#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "MouseIdler.h"

bool systemIdle(const int idleForSeconds) {
   LASTINPUTINFO lastInputInfo;
   lastInputInfo.cbSize = sizeof(lastInputInfo);
   GetLastInputInfo(&lastInputInfo);

   return GetTickCount() - lastInputInfo.dwTime >= idleForSeconds;
}

int main() {

   std::cout << "Hello world!" << "\n";
   MouseIdler::getInstance().move();
}