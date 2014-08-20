#include <ogc/isfs.h>
#include <gctypes.h>
#include "haveNandAccess.h"
//version finale
extern bool haveNANDAccess;
bool haveNandAccess() {
s32 intFd;
    if (!haveNANDAccess) {
        if ((intFd=ISFS_Open("/title/00000001/00000002/content/title.tmd",ISFS_OPEN_RW))>-1) {
            haveNANDAccess=true;
            ISFS_Close(intFd);
        }
    }
    return haveNANDAccess;
}
