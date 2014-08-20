#include "getArrayItemIndex.h"
#include "isInArray.h"
//version finale
bool isInArray(const void *varItems,unsigned int intItemsCount,int intItemSize,const void *varItem,bool blnSorted) {
    return (getArrayItemIndex(varItems,intItemsCount,intItemSize,varItem,blnSorted)<intItemsCount);
}
