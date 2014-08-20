#include <stdio.h>
#include <string.h>
#include <ogc/isfs.h>
#include "../nand/renameNandFolder.h"
#include "../titles/titles.h"
#include "moveMiosNandItems.h"
//version finale
bool moveMiosNandItems(unsigned char chDestMiosIndex) {
static char strNandDestPath[38];
bool varout=false;
    if (chDestMiosIndex) {
        snprintf(strNandDestPath,sizeof(strNandDestPath),"/title/00000001/%08x",MIOS_MINOR_TID+chDestMiosIndex);
        if (renameNandFolder("/title/00000001/00000101",&strNandDestPath[16])==ISFS_OK) {
            strcat(strNandDestPath,"/00000101.tik");
            varout=(ISFS_Rename("/ticket/00000001/00000101.tik",strNandDestPath)==ISFS_OK);
        }
    }
    else {
        varout=true;
    }
    return varout;
}
