#include "libmemory.h"
#include "setFloatItem.h"
//version finale
void *setFloatItem(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,float,GET_MEMORY_CAST_VALUE(varNumberItem,float));
    return *varNumber;
}
