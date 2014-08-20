#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stddef.h>
#include <ogc/isfs.h>
#include <gctypes.h>
#include "../../clibs/libarray/insertArrayItems.h"
#include "../../clibs/libmemory/libmemory.h"
#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "../../clibs/clibs.h"
#include "nand.h"
#include "getNandFolderContent.h"
//version finale
char **getNandFolderContent(const char *strNandFolderPath,bool blnRecursive,int *intDirectoryItemsCount) {
char *strDirectoryItems=NULL,**varout=NULL,**strFolderItems=NULL,*strDirectoryItem,strDirectoryItemPath[NAND_PATH_MAXLENGTH];
s32 intReturnValue;
int intFolderItemsCount;
unsigned char chAddSlashChar;
    *intDirectoryItemsCount=0;
    if ((intReturnValue=ISFS_ReadDir(strNandFolderPath,NULL,(u32 *) intDirectoryItemsCount))<0) {
        *intDirectoryItemsCount=intReturnValue;
    }
    else {
        if (*intDirectoryItemsCount) {
            if ((strDirectoryItems=GET_ALIGNED_MEMORY(*intDirectoryItemsCount*NAND_PATH_MAXLENGTH,32))==NULL) {
                *intDirectoryItemsCount=-1;
            }
            else {
                if ((intReturnValue=ISFS_ReadDir(strNandFolderPath,strDirectoryItems,(u32 *) intDirectoryItemsCount))<0) {
                    *intDirectoryItemsCount=intReturnValue;
                }
                else {
                    if ((varout=malloc(*intDirectoryItemsCount*POINTER_TYPE_SIZE))==NULL) {
                        *intDirectoryItemsCount=-1;
                    }
                    else {
                        strDirectoryItem=strDirectoryItems;
                        chAddSlashChar=strNandFolderPath[strlen(strNandFolderPath)-1]-'/';
                        for (intReturnValue=0;intReturnValue<*intDirectoryItemsCount;intReturnValue++) {
                            snprintf(strDirectoryItemPath,NAND_PATH_MAXLENGTH,"%s%.*s%s",strNandFolderPath,chAddSlashChar,"/",strDirectoryItem);
                            varout[intReturnValue]=strdup(strDirectoryItemPath);
                            if (blnRecursive) {
                                if ((strFolderItems=getNandFolderContent(strDirectoryItemPath,blnRecursive,&intFolderItemsCount))!=NULL) {
                                    if (insertArrayItems((void **) &varout,(unsigned int *) intDirectoryItemsCount,intReturnValue+1,POINTER_TYPE_SIZE,-1*intFolderItemsCount,strFolderItems)>*intDirectoryItemsCount) {
                                        freeRecursiveVector((void ***) &strFolderItems,intFolderItemsCount);
                                        freeRecursiveVector((void ***) &varout,*intDirectoryItemsCount);
                                        *intDirectoryItemsCount=0;
                                        break;
                                    }
                                    else {
                                        intReturnValue=intReturnValue+intFolderItemsCount;
                                        freeVector((void **) &strFolderItems);
                                    }
                                }
                            }
                            strDirectoryItem=strDirectoryItem+strlen(strDirectoryItem)+1;
                        }
                    }
                }
                freeVector((void **) &strDirectoryItems);
            }
        }
    }
    return varout;
}
