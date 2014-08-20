#include <stdint.h>
#include "libmemory.h"
#include "setS64Item.h"
//version finale
void *setS64Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,int64_t,GET_MEMORY_CAST_VALUE(varNumberItem,int64_t));
    return *varNumber;
}
