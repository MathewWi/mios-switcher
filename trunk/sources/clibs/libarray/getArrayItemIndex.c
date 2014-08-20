#include "../libmemory/getMemoryItemSize.h"
#include "getArrayMemoryItemIndex.h"
#include "getArrayItemIndex.h"
//version finale
unsigned int getArrayItemIndex(const void *varItems,unsigned int intItemsCount,int intItemSize,const void *varItem,bool blnSorted) {
    return getArrayMemoryItemIndex(varItems,intItemsCount,varItem,intItemSize,getMemoryItemSize(intItemSize),blnSorted);
}
