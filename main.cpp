#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "MouseIdler.h"
#include <cstdlib>
bool systemIdle(const int idleForSeconds) {
   LASTINPUTINFO lastInputInfo;
   lastInputInfo.cbSize = sizeof(lastInputInfo);
   GetLastInputInfo(&lastInputInfo);

   return GetTickCount() - lastInputInfo.dwTime >= idleForSeconds;
}

int main() {
	std::cout << "Opening Gmail\n";
	std::system("start https://mail.google.com");
	MouseIdler::getInstance().move();
	return 0;
}