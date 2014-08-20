#include "setFontBgColor.h"
#include "video.h"
//version finale
extern enum CONSOLE_FONT_COLORS PREVIOUS_FONT_BGCOLOR;
void resetPreviousBgColor() {
    setFontBgColor(PREVIOUS_FONT_BGCOLOR);
}
