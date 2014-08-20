#include <stdlib.h>
#include <stddef.h>
#include "../libmemory/setMemoryItemFunctions.h"
#include "getArrayMemoryItemIndex.h"
//version finale
unsigned int getArrayMemoryItemIndex(const void *varMemoryItems,unsigned int intMemoryItemsCount,const void *varItem,int intItemSize,unsigned int intMemoryStepSize,bool blnSorted) {
unsigned int varout=intMemoryItemsCount,intMinVarout=0,intMaxVarout=0;
int intCmp,(*intMemoryItemCmp)(const void *,const void *,size_t);
void *(*varMemoryItem)(const void *,unsigned int,unsigned int),*(*varCurrentMemoryItem)(void **,const void *,size_t);
    if (varout) {
        setMemoryItemFunctions(intItemSize,&varMemoryItem,&intMemoryItemCmp,&varCurrentMemoryItem);
        intItemSize=abs(intItemSize);
        if (blnSorted) {
            if ((intCmp=(*intMemoryItemCmp)(varItem,(*varMemoryItem)(varMemoryItems,0,intMemoryStepSize),intItemSize))==0) {
                return 0;
            }
            else if (intCmp>0) {
                intMemoryItemsCount--;
                if ((intCmp=(*intMemoryItemCmp)(varItem,(*varMemoryItem)(varMemoryItems,intMemoryItemsCount,intMemoryStepSize),intItemSize))<1) {
                    if (intCmp<0) {
                        do {
                            if (intCmp<0) {
                                intMaxVarout=intMemoryItemsCount;
                                intMemoryItemsCount=(intMemoryItemsCount+intMinVarout)/2;
                            }
                            else {
                                intMinVarout=intMemoryItemsCount;
                                intMemoryItemsCount=(intMaxVarout+intMemoryItemsCount)/2;
                            }
                        } while ((intMemoryItemsCount<intMaxVarout) && (intMemoryItemsCount>intMinVarout) && ((intCmp=(*intMemoryItemCmp)(varItem,(*varMemoryItem)(varMemoryItems,intMemoryItemsCount,intMemoryStepSize),intItemSize))));
                    }
                    if (!intCmp) {
                        varout=intMemoryItemsCount;
                        while (intMemoryItemsCount) {
                            intMemoryItemsCount--;
                            if ((*intMemoryItemCmp)(varItem,(*varMemoryItem)(varMemoryItems,intMemoryItemsCount,intMemoryStepSize),intItemSize)) {
                                return varout;
                            }
                            else {
                                varout=intMemoryItemsCount;
                            }
                        }
                    }
                }
            }
        }
        else {
            varout=0;
            while (varout<intMemoryItemsCount) {
                if ((*intMemoryItemCmp)(varItem,(*varMemoryItem)(varMemoryItems,varout,intMemoryStepSize),intItemSize)) {
                    varout++;
                }
                else {
                    return varout;
                }
            }
        }
    }
    return varout;
}
