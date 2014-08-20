#include <stdint.h>
#include "../macros.h"
#include "libmemory.h"
#include "getU16Cmp.h"
//version finale
int getU16Cmp(const void *varNumber1,const void *varNumber2,size_t intMemorySize) {
    return DELTA_SIGN(GET_MEMORY_CAST_VALUE(varNumber1,uint16_t),GET_MEMORY_CAST_VALUE(varNumber2,uint16_t));
}
