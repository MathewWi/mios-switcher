#include <stdlib.h>
#include "getClonedBuffer.h"
#include "dynamicMemory.h"
void *dynamicMemory(void **varMemory,size_t intMemorySize,size_t intBlockSize) {
void *varMemoryLocation=*varMemory;
    *varMemory=NULL;
    *varMemory=getClonedBuffer(varMemoryLocation,intMemorySize,intBlockSize);
    return *varMemory;
}
