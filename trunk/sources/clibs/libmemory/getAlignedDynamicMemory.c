#include <stdlib.h>
#include "libmemory.h"
#include "getAlignedDynamicMemory.h"
//version finale
void *getAlignedDynamicMemory(size_t intMemorySize,size_t intBlockSize) {
    if (intMemorySize) {
        return GET_ALIGNED_MEMORY(intMemorySize,intBlockSize);
    }
    else {
        return NULL;
    }
}
