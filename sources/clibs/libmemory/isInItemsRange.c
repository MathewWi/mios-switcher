#include <stddef.h>
#include <stdlib.h>
#include "setMemoryItemFunctions.h"
#include "isInItemsRange.h"
//version finale
signed char isInItemsRange(const void *varItem,const void *varMinItem,const void *varMaxItem,int intItemSize,bool blnIncludeMinRange,bool blnIncludeMaxRange) {
int (*intMemoryItemCmp)(const void *,const void *,size_t);
void *(*varMemoryItem)(const void *,unsigned int,unsigned int),*(*varCurrentMemoryItem)(void **,const void *,size_t);
    setMemoryItemFunctions(intItemSize,&varMemoryItem,&intMemoryItemCmp,&varCurrentMemoryItem);
    intItemSize=abs(intItemSize);
    if ((*intMemoryItemCmp)(varItem,varMinItem,intItemSize)>-1*((int) blnIncludeMinRange)) {
        if ((*intMemoryItemCmp)(varItem,varMaxItem,intItemSize)<(int) blnIncludeMaxRange) {
            return 0;
        }
        else {
            return 1;
        }
    }
    else {
        return -1;
    }
}
