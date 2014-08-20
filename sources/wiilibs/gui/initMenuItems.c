#include "../gui/printLabel.h"
#include "../video/video.h"
#include "initMenuItems.h"
void initMenuItems(struct stLabel *stLabelsSettings,unsigned char chMenuItemsCount) {
struct stConsoleCursorLocation stTexteLocation;
    while (chMenuItemsCount) {
        chMenuItemsCount--;
        printLabel(stLabelsSettings[chMenuItemsCount].stLabelLocation.intRow,stLabelsSettings[chMenuItemsCount].stLabelLocation.intColumn,CONSOLE_FONT_BLACK,CONSOLE_FONT_BLACK,CONSOLE_FONT_WHITE,stLabelsSettings[chMenuItemsCount].chLabelSize,&stTexteLocation,"","");
    }
}
