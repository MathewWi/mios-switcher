#include "../libmemory/getMemoryItemSize.h"
#include "getArrayMemoryItemCount.h"
#include "getArrayItemCount.h"
unsigned int getArrayItemCount(const void *varItems,unsigned int intItemsCount,const void *varItem,int intItemSize,bool blnSorted,unsigned int **intItemIndexes) {
    return getArrayMemoryItemCount(varItems,intItemsCount,getMemoryItemSize(intItemSize),varItem,intItemSize,blnSorted,intItemIndexes);
}
