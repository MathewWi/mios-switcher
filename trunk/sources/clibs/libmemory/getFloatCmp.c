#include "../macros.h"
#include "libmemory.h"
#include "getFloatCmp.h"
//version finale
int getFloatCmp(const void *varNumber1,const void *varNumber2,size_t intMemorySize) {
    return DELTA_SIGN(GET_MEMORY_CAST_VALUE(varNumber1,float),GET_MEMORY_CAST_VALUE(varNumber2,float));
}
