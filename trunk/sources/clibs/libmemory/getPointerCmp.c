#include "../macros.h"
#include "getPointerCmp.h"
//version finale
int getPointerCmp(const void *varPointer1,const void *varPointer2,size_t intMemorySize) {
    return DELTA_SIGN(varPointer1,varPointer2);
}
