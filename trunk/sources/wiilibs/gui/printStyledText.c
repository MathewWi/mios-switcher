#include "../video/setFontStyle.h"
#include "../video/resetPreviousFontStyle.h"
#include "printLocatedText.h"
#include "printStyledText.h"
//version finale
void printStyledText(u8 chRow,u8 chColumn,enum CONSOLE_FONT_COLORS FONT_BGCOLOR,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,struct stConsoleCursorLocation *stTexteLocation,const char *strText) {
    setFontStyle(FONT_BGCOLOR,FONT_FGCOLOR,FONT_WEIGHT);
    printLocatedText(chRow,chColumn,stTexteLocation,"%s",strText);
    resetPreviousFontStyle();
}
