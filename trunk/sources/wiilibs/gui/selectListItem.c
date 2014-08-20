#include "../../clibs/libtools/printTruncatedText.h"
#include "../video/saveCursorPosition.h"
#include "../video/setCursorPosition.h"
#include "../video/setFontFgColor.h"
#include "../video/resetPreviousFgColor.h"
#include "../video/resetSavedCursorPosition.h"
#include "../video/video.h"
#include "destroyList.h"
#include "drawList.h"
#include "selectListItem.h"
void selectListItem(struct stGuiList *stListSettings,unsigned int intSelectedListItemIndex) {
    if (intSelectedListItemIndex<stListSettings->intListItemsCount) {
        if (intSelectedListItemIndex!=stListSettings->intSelectedListItemIndex) {
            if (stListSettings->stLabelsSettings[intSelectedListItemIndex].chLabelSize) {
                saveCursorPosition();
                setCursorPosition(stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].stLabelLocation.intRow,stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].stLabelLocation.intColumn);
                setFontFgColor(stListSettings->LIST_FONT_COLOR,CONSOLE_FONT_BOLD);
                printTruncatedText("...",stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].chLabelSize,stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].chLabelSize?&stListSettings->stListItems[stListSettings->intSelectedListItemIndex].strLabel[stListSettings->intListItemsHiddenPrefixSize]:"");
                resetPreviousFgColor();
                setCursorPosition(stListSettings->stLabelsSettings[intSelectedListItemIndex].stLabelLocation.intRow,stListSettings->stLabelsSettings[intSelectedListItemIndex].stLabelLocation.intColumn);
                setFontFgColor(stListSettings->ACTIVE_ITEM_COLOR,CONSOLE_FONT_BOLD);
                printTruncatedText("...",stListSettings->stLabelsSettings[intSelectedListItemIndex].chLabelSize,stListSettings->stLabelsSettings[intSelectedListItemIndex].chLabelSize?&stListSettings->stListItems[intSelectedListItemIndex].strLabel[stListSettings->intListItemsHiddenPrefixSize]:"");
                resetPreviousFgColor();
                resetSavedCursorPosition();
                stListSettings->intSelectedListItemIndex=intSelectedListItemIndex;
            }
            else {
                destroyList(stListSettings,true);
                drawList(stListSettings->chRow,stListSettings->chColumn,stListSettings->chFieldSize,stListSettings->LIST_FONT_COLOR,stListSettings->ACTIVE_ITEM_COLOR,stListSettings->stListItems,stListSettings->intListItemsCount,stListSettings->chVisibleListItemsCount,stListSettings->intListItemsHiddenPrefixSize,stListSettings->chItemsInterlines,intSelectedListItemIndex,stListSettings->strPrependItemString,stListSettings->strAppendItemString,stListSettings->chMarkerOffset,stListSettings);
            }
        }
    }
}
