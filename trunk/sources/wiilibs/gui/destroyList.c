#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../clibs/libmemory/freeVector.h"
#include "../video/saveCursorPosition.h"
#include "../video/setCursorPosition.h"
#include "../video/resetSavedCursorPosition.h"
#include "../menu/menu.h"
#include "destroyList.h"
void destroyList(struct stGuiList *stListSettings,bool blnClearList) {
size_t intPrependItemStringSize,intAppendItemStringSize;
    if (stListSettings->stLabelsSettings!=NULL) {
        if (blnClearList) {
            saveCursorPosition();
            stListSettings->intSelectedListItemIndex=LIST_PAGE_START_ITEM_INDEX(stListSettings->intSelectedListItemIndex,stListSettings->chVisibleListItemsCount);
            intPrependItemStringSize=strlen(stListSettings->strPrependItemString);
            intAppendItemStringSize=strlen(stListSettings->strAppendItemString);
            while (stListSettings->intSelectedListItemIndex<stListSettings->intListItemsCount) {
                if (stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].chLabelSize) {
                    setCursorPosition(stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].stLabelLocation.intRow,stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].stLabelLocation.intColumn-intPrependItemStringSize);
                    printf("%*s",stListSettings->stLabelsSettings[stListSettings->intSelectedListItemIndex].chLabelSize+intPrependItemStringSize+intAppendItemStringSize,"");
                    stListSettings->intSelectedListItemIndex=stListSettings->intSelectedListItemIndex+1;
                }
                else {
                    break;
                }
            }
            resetSavedCursorPosition();
        }
        freeVector((void **) &stListSettings->stLabelsSettings);
    }
}
