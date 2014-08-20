#include "setFontBgColor.h"
#include "setFontFgColor.h"
#include "setFontStyle.h"
//version finale
void setFontStyle(enum CONSOLE_FONT_COLORS FONT_BGCOLOR,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT) {
    setFontBgColor(FONT_BGCOLOR);
    setFontFgColor(FONT_FGCOLOR,FONT_WEIGHT);
}
