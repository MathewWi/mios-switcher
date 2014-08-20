#include <stdlib.h>
#include <stddef.h>
#include "../libmemory/setMemoryItemFunctions.h"
//version finale
unsigned int getArrayMinMemoryItemIndex(const void *varMemoryItems,unsigned int intMemoryItemsCount,int intItemSize,unsigned int intMemoryStepSize) {
unsigned int varout=0;
void *pItem,*pMinItem,*(*varMemoryItem)(const void *,unsigned int,unsigned int),*(*varCurrentMemoryItem)(void **,const void *,size_t);
int (*intMemoryItemCmp)(const void *,const void *,size_t);
    setMemoryItemFunctions(intItemSize,&varMemoryItem,&intMemoryItemCmp,&varCurrentMemoryItem);
    intItemSize=abs(intItemSize);
    pMinItem=(*varMemoryItem)(varMemoryItems,0,intMemoryStepSize);
    while (intMemoryItemsCount>1) {
        intMemoryItemsCount--;
        pItem=(*varMemoryItem)(varMemoryItems,intMemoryItemsCount,intMemoryStepSize);
        if ((*intMemoryItemCmp)(pItem,pMinItem,intItemSize)<0) {
            pMinItem=pItem;
            varout=intMemoryItemsCount;
        }
    }
    return varout;
}
