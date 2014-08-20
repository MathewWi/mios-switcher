#include <stdint.h>
#include "../macros.h"
#include "libmemory.h"
#include "getS8Cmp.h"
//version finale
int getS8Cmp(const void *varNumber1,const void *varNumber2,size_t intMemorySize) {
    return DELTA_SIGN(GET_MEMORY_CAST_VALUE(varNumber1,int8_t),GET_MEMORY_CAST_VALUE(varNumber2,int8_t));
}
