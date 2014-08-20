#include <stdlib.h>
#include <gctypes.h>
#include <ogc/isfs.h>
#include "isNandDirectory.h"
//version finale
bool isNandDirectory(const char *strDirectoryPath) {
u32 intFolderItemsCount=0;
    return (ISFS_ReadDir(strDirectoryPath,NULL,&intFolderItemsCount)>-1);
}
