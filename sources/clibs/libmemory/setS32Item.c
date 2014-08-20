#include <stdint.h>
#include "libmemory.h"
#include "setS32Item.h"
//version finale
void *setS32Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,int32_t,GET_MEMORY_CAST_VALUE(varNumberItem,int32_t));
    return *varNumber;
}
