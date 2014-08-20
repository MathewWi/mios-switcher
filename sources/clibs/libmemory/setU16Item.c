#include <stdint.h>
#include "libmemory.h"
#include "setU16Item.h"
//version finale
void *setU16Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,uint16_t,GET_MEMORY_CAST_VALUE(varNumberItem,uint16_t));
    return *varNumber;
}
