#include "markListItem.h"
#include "markAllListItems.h"
void markAllListItems(struct stGuiList *stListSettings,char chMarkChar,enum CONSOLE_FONT_COLORS FONT_COLOR) {
unsigned int i;
    for (i=0;i<stListSettings->intListItemsCount;i++) {
        markListItem(stListSettings,i,chMarkChar,FONT_COLOR);
    }
}
