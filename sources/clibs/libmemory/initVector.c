#include "getMemoryItemSize.h"
#include "initMemoryItemsVector.h"
#include "initVector.h"
void *initVector(void **varVector,unsigned int intItemsCount,size_t intItemSize,const void *varInitItem) {
    return initMemoryItemsVector(varVector,intItemsCount,getMemoryItemSize(intItemSize),intItemSize,varInitItem);
}
