#include <stdlib.h>
#include <string.h>
#include "../../clibs/libfile/getFolderContent.h"
#include "../../clibs/libfile/filterFolderContent.h"
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "getDolsList.h"
struct stListItem *getDolsList(const char *strDolsFolder,bool blnRecursive,size_t intDolMaxSize,unsigned int *intDolsCount) {
struct stListItem *varout=NULL;
unsigned int intFolderItemsCount;
char **strDolsFilename=NULL;
    *intDolsCount=0;
    if ((strDolsFilename=getFolderContent(strDolsFolder,blnRecursive,&intFolderItemsCount))!=NULL) {
        *intDolsCount=filterFolderContent(strDolsFilename,intFolderItemsCount,"dol",0,intDolMaxSize);
        if ((varout=getDynamicMemory(*intDolsCount*LIST_ITEM_STRUCTURE_SIZE))==NULL) {
            *intDolsCount=0;
        }
        else {
            for (intDolMaxSize=0;intDolMaxSize<*intDolsCount;intDolMaxSize++) {
                varout[intDolMaxSize].blnMarked=false;
                varout[intDolMaxSize].varMetaDatas=NULL;
                varout[intDolMaxSize].strLabel=strdup(strDolsFilename[intDolMaxSize]);
            }
        }
        freeRecursiveVector((void ***) &strDolsFilename,intFolderItemsCount);
    }
    return varout;
}
