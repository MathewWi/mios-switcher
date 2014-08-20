#include <stdio.h>
#include <string.h>
#include "../../clibs/libtools/printTruncatedText.h"
#include "../../clibs/macros.h"
#include "../gui/printLocatedText.h"
#include "../video/setFontFgColor.h"
#include "../video/resetPreviousFgColor.h"
#include "../video/setFontBgColor.h"
#include "../video/resetPreviousBgColor.h"
#include "../video/resetSavedPreviousCursorPosition.h"
#include "printListItem.h"
//version finale
void printListItem(u8 chRow,u8 chColumn,const char *strListLabel,unsigned int intCurrentItemId,unsigned int intListItemsCount,enum CONSOLE_FONT_COLORS HIGHLIGHT_ITEM_COLOR,const char *strPrependString,const char *strAppendString,unsigned char chFieldSize,const char *strItemValue,const char *strOverflowString) {
struct stConsoleCursorLocation stListItemLocation;
    stListItemLocation.intRow=chFieldSize-printLocatedText(chRow,chColumn,&stListItemLocation,"%s%s ",strPrependString,strListLabel)-2-strlen(strAppendString);
    if (intCurrentItemId) {
        printf("<");
    }
    else {
        setFontFgColor(CONSOLE_FONT_YELLOW,CONSOLE_FONT_NORMAL);
        printf("<");
        resetPreviousFgColor();
    }
    setFontBgColor(HIGHLIGHT_ITEM_COLOR);
    stListItemLocation.intRow=stListItemLocation.intRow-printTruncatedText(strOverflowString,stListItemLocation.intRow,strItemValue);
    resetPreviousBgColor();
    if (intCurrentItemId<intListItemsCount-1) {
        printf(">");
    }
    else {
        setFontFgColor(CONSOLE_FONT_YELLOW,CONSOLE_FONT_NORMAL);
        printf(">");
        resetPreviousFgColor();
    }
    printf("%s%*s",strAppendString,MAX(stListItemLocation.intRow,0),"");
    resetSavedPreviousCursorPosition();
}
