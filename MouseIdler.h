//
// Created by User on 4/12/2026.
//

#ifndef WFH_PROMAX_MOUSEIDLER_H
#define WFH_PROMAX_MOUSEIDLER_H
#include <atomic>
#include <minwindef.h>
#include <windef.h>


class MouseIdler {
    public:
    // singleton
    static MouseIdler& getInstance() {
        static MouseIdler instance {};
        return instance;
    }
    void operator =(MouseIdler&) = delete;
    MouseIdler(MouseIdler const&) = delete;
    MouseIdler(MouseIdler&&) = delete;
    void move() ;

    private:
    const int intervalDuration;
    std::atomic<bool> keyPressed;
    std::atomic<bool> hookReady;

    static void moveLeft();
    static void moveRight();
    static LRESULT LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    void setHook() ;
    MouseIdler();

};


#endif //WFH_PROMAX_MOUSEIDLER_H