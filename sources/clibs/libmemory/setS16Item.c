#include <stdint.h>
#include "libmemory.h"
#include "setS16Item.h"
//version finale
void *setS16Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,int16_t,GET_MEMORY_CAST_VALUE(varNumberItem,int16_t));
    return *varNumber;
}
