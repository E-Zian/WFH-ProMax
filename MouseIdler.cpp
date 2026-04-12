#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include "MouseIdler.h"

HHOOK windowHookId;

LRESULT CALLBACK MouseIdler::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (const auto key{reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam)}; key->vkCode > 0 && wParam == WM_KEYDOWN) {
            getInstance().keyPressed = true;
            std::cout << "Exiting" << std::endl;
        }
    }

    return CallNextHookEx(windowHookId, nCode, wParam, lParam);
}

void MouseIdler::setHook() {
    windowHookId = SetWindowsHookExA(WH_KEYBOARD_LL, LowLevelKeyboardProc, nullptr, 0);

    if (!windowHookId) {
        std::cout << "Hook set error, Exiting" << std::endl;
        std::exit(0);
    }
    hookReady = true;
    std::cout << "Hook set successfully, Press any key to exit" << std::endl;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        DispatchMessage(&msg);
    }

    std::cout << "removing hook";
    UnhookWindowsHookEx(windowHookId);
}

MouseIdler::MouseIdler() : intervalDuration{2}, keyPressed{false},
                           hookReady{false} {
}


void MouseIdler::moveLeft() {
    INPUT mouseLeftInput{};
    mouseLeftInput.type = INPUT_MOUSE;
    mouseLeftInput.mi.dx = -100;
    mouseLeftInput.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &mouseLeftInput, sizeof(INPUT));
}


void MouseIdler::moveRight() {
    INPUT mouseRightInput{};
    mouseRightInput.type = INPUT_MOUSE;
    mouseRightInput.mi.dx = 100;
    mouseRightInput.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &mouseRightInput, sizeof(INPUT));
}

void MouseIdler::move() {
    std::jthread listenerThread([this]() { setHook(); });

    while (!hookReady) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    bool alternate = true;
    while (!keyPressed) {
        alternate ? moveLeft() : moveRight();
        alternate = !alternate;
        std::this_thread::sleep_for(std::chrono::seconds(intervalDuration));
    }

    // Reset
    PostThreadMessageA(GetThreadId(listenerThread.native_handle()), WM_QUIT, 0, 0);
    keyPressed = false;
    hookReady=false;
}
