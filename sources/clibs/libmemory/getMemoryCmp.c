#include <string.h>
#include "getMemoryCmp.h"
//version finale
int getMemoryCmp(const void *varMemory1,const void *varMemory2,size_t intMemorySize) {
    return memcmp(varMemory1,varMemory2,intMemorySize);
}
