#include "setFontFgColor.h"
#include "video.h"
//version finale
extern enum CONSOLE_FONT_WEIGHTS PREVIOUS_FONT_WEIGHT;
extern enum CONSOLE_FONT_COLORS PREVIOUS_FONT_FGCOLOR;
void resetPreviousFgColor() {
    setFontFgColor(PREVIOUS_FONT_FGCOLOR,PREVIOUS_FONT_WEIGHT);
}
