#include "../libmemory/getMemoryItemSize.h"
#include "getArrayMaxMemoryItemIndex.h"
//version finale
unsigned int getArrayMaxItemIndex(const void *varItems,unsigned int intItemsCount,int intItemSize) {
    return getArrayMaxMemoryItemIndex(varItems,intItemsCount,intItemSize,getMemoryItemSize(intItemSize));
}
