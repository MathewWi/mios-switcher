#include "libmemory.h"
#include "setDoubleItem.h"
//version finale
void *setDoubleItem(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,double,GET_MEMORY_CAST_VALUE(varNumberItem,double));
    return *varNumber;
}
