#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "../../clibs/libmath/isInRange.h"
#include "../../clibs/libtools/printTruncatedText.h"
#include "../../clibs/macros.h"
#include "../../main.h"
#include "../video/saveCursorPosition.h"
#include "../video/setCursorPosition.h"
#include "../video/getCursorPositions.h"
#include "../video/setFontFgColor.h"
#include "../video/resetPreviousFgColor.h"
#include "../video/resetSavedCursorPosition.h"
#include "../menu/menu.h"
#include "getTextBoxRow.h"
#include "getTextBoxColumn.h"
#include "markListItem.h"
#include "drawList.h"
void drawList(u8 chRow,u8 chColumn,unsigned char chFieldSize,enum CONSOLE_FONT_COLORS LIST_FONT_COLOR,enum CONSOLE_FONT_COLORS ACTIVE_ITEM_COLOR,struct stListItem *stListItems,unsigned int intListItemsCount,unsigned char chVisibleListItemsCount,size_t intListItemsHiddenPrefixSize,unsigned char chItemsInterlines,unsigned int intSelectedListItemIndex,const char *strPrependItemString,const char *strAppendItemString,signed char chMarkerOffset,struct stGuiList *stListSettings) {
size_t intPrependItemStringSize,intAppendItemStringSize;
    if ((stListSettings->stLabelsSettings=calloc(intListItemsCount,LABEL_STRUCTURE_SIZE))==NULL) {
        stListSettings->intListItemsCount=0;
    }
    else {
        chRow=getTextBoxRow(chRow);
        chColumn=getTextBoxColumn(chColumn);
        stListSettings->intListItemsCount=intListItemsCount;
        stListSettings->intListItemsHiddenPrefixSize=intListItemsHiddenPrefixSize;
        stListSettings->chRow=chRow;
        stListSettings->chColumn=chColumn;
        stListSettings->chItemsInterlines=chItemsInterlines;
        stListSettings->chVisibleListItemsCount=chVisibleListItemsCount;
        stListSettings->chFieldSize=chFieldSize;
        stListSettings->strPrependItemString=strPrependItemString;
        stListSettings->strAppendItemString=strAppendItemString;
        intPrependItemStringSize=strlen(strPrependItemString);
        intAppendItemStringSize=strlen(strAppendItemString);
        if (!isInRange(chMarkerOffset,-1*(double) intPrependItemStringSize,intAppendItemStringSize,true,true)) {
            stListSettings->chMarkerOffset=chMarkerOffset;
        }
        else {
            stListSettings->chMarkerOffset=0;
        }
        stListSettings->intSelectedListItemIndex=(intSelectedListItemIndex<intListItemsCount)?intSelectedListItemIndex:0;
        stListSettings->LIST_FONT_COLOR=LIST_FONT_COLOR;
        stListSettings->ACTIVE_ITEM_COLOR=ACTIVE_ITEM_COLOR;
        stListSettings->stListItems=stListItems;
        saveCursorPosition();
        setCursorPosition(chRow,chColumn);
        chFieldSize=chFieldSize-intPrependItemStringSize-intAppendItemStringSize;
        intListItemsCount=LIST_PAGE_START_ITEM_INDEX(stListSettings->intSelectedListItemIndex,chVisibleListItemsCount);
        intSelectedListItemIndex=stListSettings->intListItemsCount-intListItemsCount;
        intSelectedListItemIndex=MIN(intSelectedListItemIndex,chVisibleListItemsCount);
        intSelectedListItemIndex=intListItemsCount+intSelectedListItemIndex;
        while (intListItemsCount<intSelectedListItemIndex) {
            stListSettings->stLabelsSettings[intListItemsCount].chLabelSize=strlen(stListItems[intListItemsCount].strLabel)-intListItemsHiddenPrefixSize;
            stListSettings->stLabelsSettings[intListItemsCount].chLabelSize=MIN(stListSettings->stLabelsSettings[intListItemsCount].chLabelSize,chFieldSize);
            printf("%s",strPrependItemString);
            getCursorPositions(&stListSettings->stLabelsSettings[intListItemsCount].stLabelLocation.intColumn,&stListSettings->stLabelsSettings[intListItemsCount].stLabelLocation.intRow);
            setFontFgColor((intListItemsCount==stListSettings->intSelectedListItemIndex)?ACTIVE_ITEM_COLOR:LIST_FONT_COLOR,CONSOLE_FONT_BOLD);
            printTruncatedText("...",stListSettings->stLabelsSettings[intListItemsCount].chLabelSize,stListSettings->stLabelsSettings[intListItemsCount].chLabelSize?&stListItems[intListItemsCount].strLabel[intListItemsHiddenPrefixSize]:"");
            resetPreviousFgColor();
            printf("%s",strAppendItemString);
            if (chItemsInterlines) {
                chRow=chRow+chItemsInterlines;
                setCursorPosition(chRow,chColumn);
            }
            if (stListItems[intListItemsCount].blnMarked) {
                markListItem(stListSettings,intListItemsCount,254,DEFAULT_FONT_FGCOLOR);
            }
            intListItemsCount++;
        }
        resetSavedCursorPosition();
    }
}
