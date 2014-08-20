#include <string.h>
#include <stdlib.h>
#include "../libmemory/reallocBuffer.h"
#include "../libmemory/freeRecursiveVector.h"
#include "../libmemory/getDynamicMemory.h"
#include "../clibs.h"
#include "getBreakString.h"
#include "getBreakStrings.h"
//version finale
char **getBreakStrings(const char *strValue,char chBreakChar,size_t intMaxLineSize,unsigned int *intBreakStringsCount) {
char **varout=NULL,*chCurrentOffset;
unsigned int intItemsCount=0;
    if ((varout=getDynamicMemory(*intBreakStringsCount*POINTER_TYPE_SIZE))!=NULL) {
        chCurrentOffset=(char *) &strValue[0];
        while ((*chCurrentOffset) && (intItemsCount<*intBreakStringsCount)) {
            if ((varout[intItemsCount]=getBreakString(chCurrentOffset,chBreakChar,intMaxLineSize))==NULL) {
                freeRecursiveVector((void ***) &varout,intItemsCount);
                return NULL;
            }
            else {
                chCurrentOffset=chCurrentOffset+strlen(varout[intItemsCount]);
                intItemsCount++;
                chCurrentOffset=chCurrentOffset+((char) (*chCurrentOffset==chBreakChar));
            }
        }
        if (intItemsCount<*intBreakStringsCount) {
            *intBreakStringsCount=intItemsCount;
            reallocBuffer((void **) &varout,intItemsCount*POINTER_TYPE_SIZE,0);
        }
    }
    return varout;
}
