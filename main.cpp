#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "MouseIdler.h"

int main() {
   MouseIdler::getInstance().move();
}