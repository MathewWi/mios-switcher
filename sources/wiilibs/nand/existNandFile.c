#include <ogc/isfs.h>
#include <gctypes.h>
#include "existNandFile.h"
//version finale
bool existNandFile(const char *strFileName) {
s32 intFd;
    if ((intFd=ISFS_Open(strFileName,ISFS_OPEN_READ))<0) {
        return false;
    }
    else {
        ISFS_Close(intFd);
        return true;
    }
}
