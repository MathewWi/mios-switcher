#include <stdio.h>
#include "../video/saveCursorPosition.h"
#include "../video/setCursorPosition.h"
#include "../video/setFontFgColor.h"
#include "../video/resetPreviousFgColor.h"
#include "../video/resetSavedCursorPosition.h"
#include "markListItem.h"
void markListItem(struct stGuiList *stListSettings,unsigned int intSelectedListItemIndex,char chMarkChar,enum CONSOLE_FONT_COLORS FONT_COLOR) {
    if (intSelectedListItemIndex<stListSettings->intListItemsCount) {
        stListSettings->stListItems[intSelectedListItemIndex].blnMarked=(chMarkChar!=' ');
        if (stListSettings->chMarkerOffset) {
            if (stListSettings->stLabelsSettings[intSelectedListItemIndex].chLabelSize) {
                saveCursorPosition();
                if (stListSettings->chMarkerOffset>0) {
                    setCursorPosition(stListSettings->stLabelsSettings[intSelectedListItemIndex].stLabelLocation.intRow,stListSettings->stLabelsSettings[intSelectedListItemIndex].stLabelLocation.intColumn+stListSettings->stLabelsSettings[intSelectedListItemIndex].chLabelSize+stListSettings->chMarkerOffset-1);
                }
                else {
                    setCursorPosition(stListSettings->stLabelsSettings[intSelectedListItemIndex].stLabelLocation.intRow,stListSettings->stLabelsSettings[intSelectedListItemIndex].stLabelLocation.intColumn+stListSettings->chMarkerOffset);
                }
                setFontFgColor(FONT_COLOR,CONSOLE_FONT_BOLD);
                printf("%c",chMarkChar);
                resetPreviousFgColor();
                resetSavedCursorPosition();
            }
        }
    }
}
