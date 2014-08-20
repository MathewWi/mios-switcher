#include <stdint.h>
#include "libmemory.h"
#include "setU64Item.h"
//version finale
void *setU64Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,uint64_t,GET_MEMORY_CAST_VALUE(varNumberItem,uint64_t));
    return *varNumber;
}
