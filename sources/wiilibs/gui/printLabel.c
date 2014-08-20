#include <stdio.h>
#include <string.h>
#include "../../clibs/libtools/printTruncatedText.h"
#include "../video/saveCursorPosition.h"
#include "../video/setCursorPosition.h"
#include "../video/setFontStyle.h"
#include "../video/getCursorPositions.h"
#include "../video/resetPreviousFontStyle.h"
#include "../video/resetSavedCursorPosition.h"
#include "getTextBoxRow.h"
#include "getTextBoxColumn.h"
#include "printLabel.h"
//version finale
void printLabel(u8 chRow,u8 chColumn,enum CONSOLE_FONT_COLORS FONT_BGCOLOR,enum CONSOLE_FONT_COLORS FONT_FGCOLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT,unsigned char chLabelSize,struct stConsoleCursorLocation *stConcatLabelLocation,const char *strLabel,const char *strOverflowString) {
    saveCursorPosition();
    setCursorPosition(getTextBoxRow(chRow),getTextBoxColumn(chColumn));
    setFontStyle(FONT_BGCOLOR,FONT_FGCOLOR,FONT_WEIGHT);
    if (chLabelSize) {
        printf("%*s",(unsigned int) chLabelSize-printTruncatedText(strOverflowString,chLabelSize,strLabel),"");
    }
    else {
        printf("%s",strLabel);
    }
    getCursorPositions(&stConcatLabelLocation->intColumn,&stConcatLabelLocation->intRow);
    resetPreviousFontStyle();
    resetSavedCursorPosition();
}
