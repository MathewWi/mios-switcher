#include <stdlib.h>
#include <stddef.h>
#include "../libmemory/getDynamicMemory.h"
#include "../libmemory/reallocBuffer.h"
#include "../libmemory/setMemoryItemFunctions.h"
#include "../clibs.h"
#include "getArrayMemoryItemIndex.h"
#include "getArrayMemoryItemCount.h"
unsigned int getArrayMemoryItemCount(const void *varMemoryItems,unsigned int intMemoryItemsCount,unsigned int intMemoryStepSize,const void *varItem,int intItemSize,bool blnSorted,unsigned int **intMemoryItemIndexes) {
void *(*varMemoryItem)(const void *,unsigned int,unsigned int),*(*varCurrentMemoryItem)(void **,const void *,size_t);
int (*intMemoryItemCmp)(const void *,const void *,size_t);
unsigned int varout=0;
    setMemoryItemFunctions(intItemSize,&varMemoryItem,&intMemoryItemCmp,&varCurrentMemoryItem);
    if ((*intMemoryItemIndexes=getDynamicMemory(intMemoryItemsCount*INT_TYPE_SIZE))!=NULL) {
        if (blnSorted) {
            if (((*intMemoryItemIndexes)[varout]=getArrayMemoryItemIndex(varMemoryItems,intMemoryItemsCount,varItem,intItemSize,intMemoryStepSize,true))<intMemoryItemsCount) {
                intItemSize=abs(intItemSize);
                varout++;
                while (((*intMemoryItemIndexes)[0]=(*intMemoryItemIndexes)[0]+1)<intMemoryItemsCount) {
                    if ((*intMemoryItemCmp)(varItem,(*varMemoryItem)(varMemoryItems,(*intMemoryItemIndexes)[0],intMemoryStepSize),intItemSize)) {
                        intMemoryItemsCount=(*intMemoryItemIndexes)[0]+1;
                    }
                    else {
                        (*intMemoryItemIndexes)[varout]=intMemoryItemsCount;
                        varout++;
                    }
                }
                (*intMemoryItemIndexes)[0]=(*intMemoryItemIndexes)[0]-varout;
            }
        }
        else {
            intItemSize=abs(intItemSize);
            while (intMemoryItemsCount) {
                intMemoryItemsCount--;
                if ((*intMemoryItemCmp)(varItem,(*varMemoryItem)(varMemoryItems,intMemoryItemsCount,intMemoryStepSize),intItemSize)==0) {
                    (*intMemoryItemIndexes)[varout]=intMemoryItemsCount;
                    varout++;
                }
            }
        }
        reallocBuffer((void **) intMemoryItemIndexes,varout*INT_TYPE_SIZE,0);
    }
    return varout;
}
