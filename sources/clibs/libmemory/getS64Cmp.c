#include <stdint.h>
#include "../macros.h"
#include "libmemory.h"
#include "getS64Cmp.h"
//version finale
int getS64Cmp(const void *varNumber1,const void *varNumber2,size_t intMemorySize) {
    return DELTA_SIGN(GET_MEMORY_CAST_VALUE(varNumber1,int64_t),GET_MEMORY_CAST_VALUE(varNumber2,int64_t));
}
