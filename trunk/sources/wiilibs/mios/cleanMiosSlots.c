#include "../nand/deleteNandTitleFolder.h"
#include "../titles/uninstallTitle.h"
#include "../titles/titles.h"
void cleanMiosSlots() {
unsigned char i=255;
    uninstallTitle(MIOS_TID,false);
    while (i) {
        deleteNandTitleFolder(MIOS_TID+i);
        i--;
    }
}
