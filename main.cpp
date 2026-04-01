#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

HHOOK windowHookId;

std::atomic<bool> keyPressed{false};
std::atomic<bool> hookReady{ false };

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >=0) {
        if (const auto key { reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam)}; key->vkCode > 0 && wParam == WM_KEYDOWN ) {
            keyPressed = true;
            std::cout << "Exiting" << std::endl;
        }
    }

    return CallNextHookEx(windowHookId, nCode, wParam, lParam);
}

void setHook() {
    windowHookId = SetWindowsHookExA(WH_KEYBOARD_LL,LowLevelKeyboardProc, nullptr,0);

    if (!windowHookId) {
            std::cout << "Hook set error, Exiting" << std::endl;
            std::exit(0);
    }
    hookReady = true;
    std::cout << "Hook set successfully" << std::endl;
    std::cout << "Press any key to exit" << std::endl;
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        // TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    std::cout << "removing hook";
    UnhookWindowsHookEx(windowHookId);
}

void moveLeft() {
    INPUT mouseLeftInput{};
    mouseLeftInput.type = INPUT_MOUSE;
    mouseLeftInput.mi.dx = -100;
    mouseLeftInput.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &mouseLeftInput, sizeof(INPUT));
}

void moveRight() {
    INPUT mouseRightInput{};
    mouseRightInput.type = INPUT_MOUSE;
    mouseRightInput.mi.dx = 100;
    mouseRightInput.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &mouseRightInput, sizeof(INPUT));
}

int main() {
    std::jthread listenerThread(setHook);

    while (!hookReady) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    while (!keyPressed) {
        moveLeft();

        moveRight();
    }

    PostThreadMessageA(GetThreadId(listenerThread.native_handle()), WM_QUIT, 0, 0);
}