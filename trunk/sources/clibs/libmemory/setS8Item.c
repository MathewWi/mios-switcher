#include <stdint.h>
#include "libmemory.h"
#include "setS8Item.h"
//version finale
void *setS8Item(void **varNumber,const void *varNumberItem,size_t intMemorySize) {
    SET_MEMORY_CAST_VALUE(*varNumber,int8_t,GET_MEMORY_CAST_VALUE(varNumberItem,int8_t));
    return *varNumber;
}
