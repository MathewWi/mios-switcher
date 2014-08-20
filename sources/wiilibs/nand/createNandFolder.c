#include <ogc/isfs.h>
#include "isNandDirectory.h"
#include "createNandFolder.h"
//version finale
s32 createNandFolder(const char *strFolderPath) {
    if (isNandDirectory(strFolderPath)) {
        return ISFS_OK;
    }
    else {
        return ISFS_CreateDir(strFolderPath,0,ISFS_OPEN_RW,ISFS_OPEN_RW,ISFS_OPEN_RW);
    }
}
