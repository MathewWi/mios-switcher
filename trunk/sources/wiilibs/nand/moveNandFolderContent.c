#include <stdio.h>
#include <stdlib.h>
#include <ogc/isfs.h>
#include <string.h>
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "nand.h"
#include "isNandDirectory.h"
#include "getNandFolderContent.h"
#include "moveNandFolderContent.h"
//version finale
s32 moveNandFolderContent(const char *strSrcFolderPath,const char *strDestFolderPath) {
s32 varout;
int intDirectoryItemsCount,i;
size_t intSrcPathLength;
char **strDirectoryItems=NULL,strDestItemPath[NAND_PATH_MAXLENGTH];
    if (isNandDirectory(strDestFolderPath)) {
        if ((strDirectoryItems=getNandFolderContent(strSrcFolderPath,false,&intDirectoryItemsCount))==NULL) {
            varout=intDirectoryItemsCount;
        }
        else {
            varout=ISFS_OK;
            intSrcPathLength=strlen(strSrcFolderPath);
            for (i=0;i<intDirectoryItemsCount;i++) {
                snprintf(strDestItemPath,NAND_PATH_MAXLENGTH,"%s%s",strDestFolderPath,strDirectoryItems[i]+intSrcPathLength);
                if ((varout=ISFS_Rename(strDirectoryItems[i],strDestItemPath))<0) {
                    break;
                }
            }
            freeRecursiveVector((void ***) &strDirectoryItems,intDirectoryItemsCount);
        }
    }
    else {
        varout=-1;
    }
    return varout;
}
