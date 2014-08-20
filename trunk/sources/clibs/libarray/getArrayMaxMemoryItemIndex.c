#include <stdlib.h>
#include <stddef.h>
#include "../libmemory/setMemoryItemFunctions.h"
//version finale
unsigned int getArrayMaxMemoryItemIndex(const void *varMemoryItems,unsigned int intMemoryItemsCount,int intItemSize,unsigned int intMemoryStepSize) {
unsigned int varout=0;
void *pItem,*pMaxItem,*(*varMemoryItem)(const void *,unsigned int,unsigned int),*(*varCurrentMemoryItem)(void **,const void *,size_t);
int (*intMemoryItemCmp)(const void *,const void *,size_t);
    setMemoryItemFunctions(intItemSize,&varMemoryItem,&intMemoryItemCmp,&varCurrentMemoryItem);
    intItemSize=abs(intItemSize);
    pMaxItem=(*varMemoryItem)(varMemoryItems,0,intMemoryStepSize);
    while (intMemoryItemsCount>1) {
        intMemoryItemsCount--;
        pItem=(*varMemoryItem)(varMemoryItems,intMemoryItemsCount,intMemoryStepSize);
        if ((*intMemoryItemCmp)(pItem,pMaxItem,intItemSize)>0) {
            pMaxItem=pItem;
            varout=intMemoryItemsCount;
        }
    }
    return varout;
}
