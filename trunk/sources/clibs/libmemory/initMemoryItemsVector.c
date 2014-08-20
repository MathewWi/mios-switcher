#include "setMemoryItemFunctions.h"
#include "initMemoryItemsVector.h"
void *initMemoryItemsVector(void **varMemoryItemsVector,unsigned int intItemsCount,size_t intMemoryStepSize,size_t intItemSize,const void *varInitItem) {
int (*intMemoryItemCmp)(const void *,const void *,size_t);
void *(*varMemoryItem)(const void *,unsigned int,unsigned int),*(*varCurrentMemoryItem)(void **,const void *,size_t),*pItem;
    if (intItemsCount) {
        setMemoryItemFunctions(intItemSize,&varMemoryItem,&intMemoryItemCmp,&varCurrentMemoryItem);
        while (intItemsCount) {
            intItemsCount--;
            pItem=(*varMemoryItem)(*varMemoryItemsVector,intItemsCount,intMemoryStepSize);
            (*varCurrentMemoryItem)(&pItem,varInitItem,intItemSize);
        }
    }
	return *varMemoryItemsVector;
}
