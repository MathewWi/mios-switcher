#include "../libmemory/getMemoryItemSize.h"
#include "getArrayMinMemoryItemIndex.h"
//version finale
unsigned int getArrayMinItemIndex(const void *varItems,unsigned int intItemsCount,int intItemSize) {
    return getArrayMinMemoryItemIndex(varItems,intItemsCount,intItemSize,getMemoryItemSize(intItemSize));
}
