#include <stdio.h>
#include "../video/getCursorPositions.h"
#include "printStyledText.h"
#include "drawLabel.h"
//version finale
void drawLabel(u8 chRow,u8 chColumn,enum CONSOLE_FONT_COLORS FONT_BGCOLOR,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,const char *strLabelCaption,u8 chLabelSize,struct stLabel *stLabelSettings,struct stConsoleCursorLocation *stLabelCaptionLocation) {
    printStyledText(chRow,chColumn,FONT_BGCOLOR,FONT_FGCOLOR,FONT_WEIGHT,stLabelCaptionLocation,strLabelCaption);
    getCursorPositions(&stLabelSettings->stLabelLocation.intColumn,&stLabelSettings->stLabelLocation.intRow);
    stLabelSettings->chLabelSize=chLabelSize;
    printf("%*s",(unsigned int) stLabelSettings->chLabelSize,"");
    fflush(stdout);
}
