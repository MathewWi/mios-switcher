#include <stdio.h>
#include <gctypes.h>
#include "getBgColorPattern.h"
#include "setFontBgColor.h"
//version finale
extern enum CONSOLE_FONT_COLORS CURRENT_FONT_FGCOLOR;
extern enum CONSOLE_FONT_COLORS PREVIOUS_FONT_BGCOLOR;
extern enum CONSOLE_FONT_COLORS CURRENT_FONT_BGCOLOR;
void setFontBgColor(enum CONSOLE_FONT_COLORS FONT_COLOR) {
    if (FONT_COLOR==CONSOLE_FONT_CURRENT_COLOR) {
        FONT_COLOR=CURRENT_FONT_FGCOLOR;
    }
    PREVIOUS_FONT_BGCOLOR=CURRENT_FONT_BGCOLOR;
    printf(getBgColorPattern(FONT_COLOR));
    CURRENT_FONT_BGCOLOR=FONT_COLOR;
}
