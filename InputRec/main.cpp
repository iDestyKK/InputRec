/*
 * Input Recorder
 *
 * Description:
 *     Records keyboard input into a replay file. This is useful for generating
 *     a "keyboard preview" for a video recording. Press F9 to start/stop the
 *     recording.
 *
 * Author:
 *     Clara Nguyen (@iDestyKK)
 */

#include <stdio.h>
#include <stdint.h>
#include <windowsx.h>
#include <Windows.h>
#include "recorder.hpp"

using namespace std;

#define REC_BTTN VK_F9

//it really comes down to this huh
recorder<uint16_t> rec_kb;
recorder<uint16_t> rec_m;

bool recording;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    PKBDLLHOOKSTRUCT p;

    if (nCode == HC_ACTION) {
        switch (wParam) {
            case WM_KEYDOWN:
                p = (PKBDLLHOOKSTRUCT) lParam;

                if (p->vkCode == REC_BTTN) {
                    if (!recording) {
                        rec_kb.record_start();
                        printf("Started recording...");
                    }
                    else {
                        printf(" Processing...");

                        rec_kb.record_stop();
                        rec_kb.record_save();

                        printf("\rStarted recording... Done.        \n");
                    }

                    recording = !recording;
                }
                else
                    rec_kb.record_capture(0x100 & p->vkCode);

                break;

            case WM_KEYUP:
                p = (PKBDLLHOOKSTRUCT)lParam;

                if (p->vkCode != REC_BTTN)
                    rec_kb.record_capture(p->vkCode);

                break;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    PMOUSEHOOKSTRUCT p;

    if (nCode == HC_ACTION) {
        switch (wParam) {
            case WM_LBUTTONDOWN:
                printf("WM_LBUTTONDOWN\n");
                break;

            case WM_LBUTTONUP:
                printf("WM_LBUTTONUP\n");
                break;

            case WM_MBUTTONDOWN:
                printf("WM_MBUTTONDOWN\n");
                break;

            case WM_MBUTTONUP:
                printf("WM_MBUTTONUP\n");
                break;

            case WM_RBUTTONDOWN:
                printf("WM_RBUTTONDOWN\n");
                break;

            case WM_RBUTTONUP:
                printf("WM_RBUTTONUP\n");
                break;

            case WM_MOUSEMOVE:
                p = (PMOUSEHOOKSTRUCT) lParam;
                printf("WM_MOUSEMOVE %d %d\n", p->pt.x, p->pt.y);
                break;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    recording = false;

    // Install the low-level keyboard & mouse hooks
    HHOOK hook_kb = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    //HHOOK hook_m  = SetWindowsHookEx(WH_MOUSE_LL   , LowLevelMouseProc   , 0, 0);

    // Keep this app running until we're told to stop
    MSG msg;
    while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook_kb);
    //UnhookWindowsHookEx(hook_m);
}
