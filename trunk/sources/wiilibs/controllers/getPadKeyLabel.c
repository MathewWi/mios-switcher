#include <wiiuse/wpad.h>
#include <ogc/pad.h>
#include "getPadKeyLabel.h"
//version finale
char *getPadKeyLabel(s32 intPadKey,enum CONTROLLERS CONTROLLER) {
static char strPadButtonNoneSymbol[]="";
static char strPadLeftButtonSymbol[]={17,0};
static char strPadRightButtonSymbol[]={16,0};
static char strPadDownButtonSymbol[]={31,0};
static char strPadUpButtonSymbol[]={30,0};
static char strPadPlusButtonSymbol[]="(+)";
static char strPadMinusButtonSymbol[]="(-)";
static char strPadAButtonSymbol[]="(A)";
static char strPadBButtonSymbol[]="(B)";
static char strWPadBButtonSymbol[]="[B]";
static char strPad1ButtonSymbol[]="(1)";
static char strPad2ButtonSymbol[]="(2)";
static char strPadHomeButtonSymbol[]="(HOME)";
static char strPadRButtonSymbol[]="[R]";
static char strPadZButtonSymbol[]="[Z]";
static char strPadXButtonSymbol[]="(X)";
static char strPadYButtonSymbol[]="(Y)";
static char strPadLButtonSymbol[]="[L]";
static char strPadStartButtonSymbol[]="(START)";
char *varout=strPadButtonNoneSymbol;
    switch (CONTROLLER) {
        case GAMECUBE_CONTROLLER:
            switch(intPadKey) {
                case PAD_BUTTON_LEFT:
                    varout=strPadLeftButtonSymbol;
                    break;
                case PAD_BUTTON_RIGHT:
                    varout=strPadRightButtonSymbol;
                    break;
                case PAD_BUTTON_DOWN:
                    varout=strPadDownButtonSymbol;
                    break;
                case PAD_BUTTON_UP:
                    varout=strPadUpButtonSymbol;
                    break;
                case PAD_TRIGGER_Z:
                    varout=strPadZButtonSymbol;
                    break;
                case PAD_TRIGGER_R:
                    varout=strPadRButtonSymbol;
                    break;
                case PAD_TRIGGER_L:
                    varout=strPadLButtonSymbol;
                    break;
                case PAD_BUTTON_A:
                    varout=strPadAButtonSymbol;
                    break;
                case PAD_BUTTON_B:
                    varout=strPadBButtonSymbol;
                    break;
                case PAD_BUTTON_Y:
                    varout=strPadYButtonSymbol;
                    break;
                case PAD_BUTTON_X:
                    varout=strPadXButtonSymbol;
                    break;
                case PAD_BUTTON_START:
                    varout=strPadStartButtonSymbol;
                    break;
            }
            break;
        case WIIMOTE_CONTROLLER:
            switch(intPadKey) {
                case WPAD_BUTTON_LEFT:
                    varout=strPadLeftButtonSymbol;
                    break;
                case WPAD_BUTTON_RIGHT:
                    varout=strPadRightButtonSymbol;
                    break;
                case WPAD_BUTTON_DOWN:
                    varout=strPadDownButtonSymbol;
                    break;
                case WPAD_BUTTON_UP:
                    varout=strPadUpButtonSymbol;
                    break;
                case WPAD_BUTTON_PLUS:
                    varout=strPadPlusButtonSymbol;
                    break;
                case WPAD_BUTTON_MINUS:
                    varout=strPadMinusButtonSymbol;
                    break;
                case WPAD_BUTTON_A:
                    varout=strPadAButtonSymbol;
                    break;
                case WPAD_BUTTON_B:
                    varout=strWPadBButtonSymbol;
                    break;
                case WPAD_BUTTON_1:
                    varout=strPad1ButtonSymbol;
                    break;
                case WPAD_BUTTON_2:
                    varout=strPad2ButtonSymbol;
                    break;
                case WPAD_BUTTON_HOME:
                    varout=strPadHomeButtonSymbol;
                    break;
            }
            break;
        case CLASSIC_CONTROLLER:
            switch(intPadKey) {
                case WPAD_CLASSIC_BUTTON_LEFT:
                    varout=strPadLeftButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_RIGHT:
                    varout=strPadRightButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_DOWN:
                    varout=strPadDownButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_UP:
                    varout=strPadUpButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_ZR:
                    varout=strPadRButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_PLUS:
                    varout=strPadPlusButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_MINUS:
                    varout=strPadMinusButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_A:
                    varout=strPadAButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_B:
                    varout=strPadBButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_Y:
                    varout=strPadYButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_X:
                    varout=strPadXButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_ZL:
                    varout=strPadLButtonSymbol;
                    break;
                case WPAD_CLASSIC_BUTTON_HOME:
                    varout=strPadHomeButtonSymbol;
                    break;
            }
            break;
    }
    return varout;
}
