#include "setFontStyle.h"
#include "video.h"
//version finale
extern enum CONSOLE_FONT_WEIGHTS PREVIOUS_FONT_WEIGHT;
extern enum CONSOLE_FONT_COLORS PREVIOUS_FONT_FGCOLOR;
extern enum CONSOLE_FONT_COLORS PREVIOUS_FONT_BGCOLOR;
void resetPreviousFontStyle() {
    setFontStyle(PREVIOUS_FONT_BGCOLOR,PREVIOUS_FONT_FGCOLOR,PREVIOUS_FONT_WEIGHT);
}
