#include "../macros.h"
#include "libmemory.h"
#include "getDoubleCmp.h"
//version finale
int getDoubleCmp(const void *varNumber1,const void *varNumber2,size_t intMemorySize) {
    return DELTA_SIGN(GET_MEMORY_CAST_VALUE(varNumber1,double),GET_MEMORY_CAST_VALUE(varNumber2,double));
}
