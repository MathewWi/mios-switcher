#include <stdint.h>
#include "libmemory.h"
#include "setU32Item.h"
//version finale
void *setU32Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,uint32_t,GET_MEMORY_CAST_VALUE(varNumberItem,uint32_t));
    return *varNumber;
}
