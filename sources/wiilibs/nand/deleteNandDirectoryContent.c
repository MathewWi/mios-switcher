#include <stdio.h>
#include <stdlib.h>
#include <ogc/isfs.h>
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "getNandFolderContent.h"
#include "deleteNandDirectoryContent.h"
//version finale
s32 deleteNandDirectoryContent(const char *strDirectoryPath) {
s32 varout;
char **strDirectoryItems=NULL;
int intDirectoryItemsCount,i;
    if ((strDirectoryItems=getNandFolderContent(strDirectoryPath,false,&intDirectoryItemsCount))==NULL) {
        varout=intDirectoryItemsCount;
    }
    else {
        varout=ISFS_OK;
        for (i=0;i<intDirectoryItemsCount;i++) {
            if ((varout=ISFS_Delete(strDirectoryItems[i]))<0) {
                if ((varout=deleteNandDirectoryContent(strDirectoryItems[i]))<0) {
                    //TODO
                    break;
                }
            }
        }
        freeRecursiveVector((void ***) &strDirectoryItems,intDirectoryItemsCount);
    }
    return varout;
}
