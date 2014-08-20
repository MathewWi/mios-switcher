#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "../macros.h"
#include "../clibs.h"
#include "../libmemory/reallocBuffer.h"
#include "../libmemory/getCharsVector.h"
#include "../libmemory/getDynamicMemory.h"
//version finale
char **getSplitStrings(const char *strValue,const char *strSeparator,unsigned int *intItemsCount) {
size_t intSeparatorSize=strlen(strValue)+1,intSplitStringSize;
char **varout=NULL,*pPreviousOffset,*pCurrentOffset;
unsigned int intSplitItemsCount=0;
    *intItemsCount=(*intItemsCount)?MIN(*intItemsCount,intSeparatorSize):intSeparatorSize;
    if ((varout=getDynamicMemory(*intItemsCount*POINTER_TYPE_SIZE))!=NULL) {
        intSeparatorSize=strlen(strSeparator);
        pPreviousOffset=(char *) strValue;
        while ((intSplitItemsCount<*intItemsCount) && ((pCurrentOffset=strstr(pPreviousOffset,strSeparator))!=NULL)) {
            intSplitStringSize=pCurrentOffset-pPreviousOffset;
            if ((varout[intSplitItemsCount]=getCharsVector(intSplitStringSize+1,intSplitStringSize,1,0))!=NULL) {
                memcpy(varout[intSplitItemsCount],pPreviousOffset,intSplitStringSize);
            }
            pPreviousOffset=pCurrentOffset+intSeparatorSize;
            intSplitItemsCount++;
        }
        if (intSplitItemsCount<*intItemsCount) {
            varout[intSplitItemsCount]=strdup(pPreviousOffset);
            *intItemsCount=intSplitItemsCount+1;
            reallocBuffer((void **) &varout,*intItemsCount*POINTER_TYPE_SIZE,0);
        }
    }
    return varout;
}
