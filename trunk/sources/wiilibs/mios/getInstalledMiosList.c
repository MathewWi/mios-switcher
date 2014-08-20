#include <stdlib.h>
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "getInstalledMiosList.h"
struct stListItem *getInstalledMiosList(struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount) {
struct stListItem *varout=NULL;
    if ((varout=getDynamicMemory(LIST_ITEM_STRUCTURE_SIZE*chInstalledMiosCount))!=NULL) {
        while (chInstalledMiosCount) {
            chInstalledMiosCount--;
            varout[chInstalledMiosCount].blnMarked=false;
            varout[chInstalledMiosCount].strLabel=stInstalledMiosInfos[chInstalledMiosCount]->strTitleLabel;
        }
    }
    return varout;
}
