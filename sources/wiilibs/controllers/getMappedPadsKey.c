#include <ogc/pad.h>
#include <wiiuse/wpad.h>
#include "getMappedPadsKey.h"
//version finale
s32 getMappedPadsKey(s32 intPadsKey) {
    switch(intPadsKey) {
        case WPAD_BUTTON_LEFT:
        case WPAD_CLASSIC_BUTTON_LEFT:
            return PAD_BUTTON_LEFT;
            break;
        case WPAD_BUTTON_RIGHT:
        case WPAD_CLASSIC_BUTTON_RIGHT:
            return PAD_BUTTON_RIGHT;
            break;
        case WPAD_BUTTON_DOWN:
        case WPAD_CLASSIC_BUTTON_DOWN:
            return PAD_BUTTON_DOWN;
            break;
        case WPAD_BUTTON_UP:
        case WPAD_CLASSIC_BUTTON_UP:
            return PAD_BUTTON_UP;
            break;
        case WPAD_CLASSIC_BUTTON_ZR:
            return PAD_TRIGGER_Z;
            break;
        case WPAD_BUTTON_PLUS:
        case WPAD_CLASSIC_BUTTON_PLUS:
            return PAD_TRIGGER_R;
            break;
        case WPAD_BUTTON_MINUS:
        case WPAD_CLASSIC_BUTTON_MINUS:
            return PAD_TRIGGER_L;
            break;
        case WPAD_BUTTON_A:
        case WPAD_CLASSIC_BUTTON_A:
            return PAD_BUTTON_A;
            break;
        case WPAD_BUTTON_B:
        case WPAD_CLASSIC_BUTTON_B:
            return PAD_BUTTON_B;
            break;
        case WPAD_BUTTON_1:
        case WPAD_CLASSIC_BUTTON_Y:
            return PAD_BUTTON_Y;
            break;
        case WPAD_BUTTON_2:
        case WPAD_CLASSIC_BUTTON_X:
            return PAD_BUTTON_X;
            break;
        case WPAD_CLASSIC_BUTTON_ZL:
            return PAD_BUTTON_MENU;
            break;
        case WPAD_BUTTON_HOME:
        case WPAD_CLASSIC_BUTTON_HOME:
            return PAD_BUTTON_START;
            break;
        default:
            return 0;
    }
}
