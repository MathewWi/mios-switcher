#include <ogc/pad.h>
#include <wiiuse/wpad.h>
#include "getUnmappedPadKey.h"
//version finale
s32 getUnmappedPadKey(s32 intMappedPadKey,enum CONTROLLERS CONTROLLER) {
s32 varout=0;
    switch(CONTROLLER) {
        case GAMECUBE_CONTROLLER:
            varout=intMappedPadKey;
            break;
        case WIIMOTE_CONTROLLER:
            switch(intMappedPadKey) {
                case PAD_BUTTON_LEFT:
                    varout=WPAD_BUTTON_LEFT;
                    break;
                case PAD_BUTTON_RIGHT:
                    varout=WPAD_BUTTON_RIGHT;
                    break;
                case PAD_BUTTON_DOWN:
                    varout=WPAD_BUTTON_DOWN;
                    break;
                case PAD_BUTTON_UP:
                    varout=WPAD_BUTTON_UP;
                    break;
                case PAD_TRIGGER_R:
                    varout=WPAD_BUTTON_PLUS;
                    break;
                case PAD_TRIGGER_L:
                    varout=WPAD_BUTTON_MINUS;
                    break;
                case PAD_BUTTON_A:
                    varout=WPAD_BUTTON_A;
                    break;
                case PAD_BUTTON_B:
                    varout=WPAD_BUTTON_B;
                    break;
                case PAD_BUTTON_Y:
                    varout=WPAD_BUTTON_1;
                    break;
                case PAD_BUTTON_X:
                    varout=WPAD_BUTTON_2;
                    break;
                case PAD_BUTTON_START:
                    varout=WPAD_BUTTON_HOME;
                    break;
            }
            break;
        case CLASSIC_CONTROLLER:
            switch(intMappedPadKey) {
                case PAD_BUTTON_LEFT:
                    varout=WPAD_CLASSIC_BUTTON_LEFT;
                    break;
                case PAD_BUTTON_RIGHT:
                    varout=WPAD_CLASSIC_BUTTON_RIGHT;
                    break;
                case PAD_BUTTON_DOWN:
                    varout=WPAD_CLASSIC_BUTTON_DOWN;
                    break;
                case PAD_BUTTON_UP:
                    varout=WPAD_CLASSIC_BUTTON_UP;
                    break;
                case PAD_TRIGGER_Z:
                    varout=WPAD_CLASSIC_BUTTON_ZR;
                    break;
                case PAD_TRIGGER_R:
                    varout=WPAD_CLASSIC_BUTTON_PLUS;
                    break;
                case PAD_TRIGGER_L:
                    varout=WPAD_CLASSIC_BUTTON_MINUS;
                    break;
                case PAD_BUTTON_A:
                    varout=WPAD_CLASSIC_BUTTON_A;
                    break;
                case PAD_BUTTON_B:
                    varout=WPAD_CLASSIC_BUTTON_B;
                    break;
                case PAD_BUTTON_Y:
                    varout=WPAD_CLASSIC_BUTTON_Y;
                    break;
                case PAD_BUTTON_X:
                    varout=WPAD_CLASSIC_BUTTON_X;
                    break;
                case PAD_BUTTON_START:
                    varout=WPAD_CLASSIC_BUTTON_HOME;
                    break;
            }
            break;
    }
    return varout;
}
