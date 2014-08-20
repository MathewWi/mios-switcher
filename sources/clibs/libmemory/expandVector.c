#include <stdlib.h>
#include "reallocBuffer.h"
#include "initVector.h"
#include "expandVector.h"
void *expandVector(void **varVector,unsigned int intItemsCount,unsigned int intAddingItemsCount,const void *varInitItem,size_t intItemSize) {
void *varNewItems;
    if (reallocBuffer(varVector,(intItemsCount+intAddingItemsCount)*intItemSize,0)!=NULL) {
        varNewItems=*varVector+intItemsCount*intItemSize;
        initVector(&varNewItems,intAddingItemsCount,intItemSize,varInitItem);
        return *varVector;
    }
    return NULL;
}
