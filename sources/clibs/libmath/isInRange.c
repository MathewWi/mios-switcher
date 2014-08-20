#include "../libmemory/isInItemsRange.h"
#include "../libmemory/libmemory.h"
#include "isInRange.h"
//version finale
signed char isInRange(double dbValue,double dbMinRangeValue,double dbMaxRangeValue,bool blnIncludeMinRange,bool blnIncludeMaxRange) {
    return isInItemsRange(&dbValue,&dbMinRangeValue,&dbMaxRangeValue,DOUBLE_MEMORY_ITEM,blnIncludeMinRange,blnIncludeMaxRange);
}
