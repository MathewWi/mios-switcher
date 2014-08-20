#include <stdint.h>
#include "libmemory.h"
#include "setU8Item.h"
//version finale
void *setU8Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,uint8_t,GET_MEMORY_CAST_VALUE(varNumberItem,uint8_t));
    return *varNumber;
}
