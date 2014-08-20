#include <string.h>
#include "../libmemory/setMemoryItemFunctions.h"
#include "../libmemory/swapMemory.h"
#include "../libmemory/freeVector.h"
#include "getArrayMemoryItemIndex.h"
#include "uniqueArray.h"
unsigned int uniqueArray(const void *varArray,size_t intItemSize,unsigned int intItemsCount,unsigned int intOffsetUniqueField,int intUniqueFieldSize) {
unsigned int varout=0;
unsigned int intArraySize;
int (*intMemoryItemCmp)(const void *,const void *,size_t);
void *(*varMemoryItem)(const void *,unsigned int,unsigned int),*(*varCurrentMemoryItem)(void **,const void *,size_t);
void **varSwapMemory=NULL,*varArrayMemoryItems=(void *) varArray+intOffsetUniqueField;
    setMemoryItemFunctions(intUniqueFieldSize,&varMemoryItem,&intMemoryItemCmp,&varCurrentMemoryItem);
    while (varout<intItemsCount) {
        intArraySize=intItemsCount-varout-1;
        if (getArrayMemoryItemIndex(varArrayMemoryItems+(varout+1)*intItemSize,intArraySize,(*varMemoryItem)(varArrayMemoryItems,varout,intItemSize),intUniqueFieldSize,intItemSize,false)<intArraySize) {
            intItemsCount--;
            if ((varSwapMemory=swapMemory((void *) varArray+varout*intItemSize,(void *) varArray+intItemsCount*intItemSize,intItemSize))==NULL) {
                return 0;
            }
        }
        else {
            varout++;
        }
    }
    freeVector(varSwapMemory);
    return varout;
}
