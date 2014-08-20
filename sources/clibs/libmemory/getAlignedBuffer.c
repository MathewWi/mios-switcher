#include "getAlignedDynamicMemory.h"
#include "getDynamicMemory.h"
#include "getAlignedBuffer.h"
//version finale
void *getAlignedBuffer(size_t intBufferSize,size_t intBlockSize) {
    if (intBlockSize) {
        return getAlignedDynamicMemory(intBufferSize,intBlockSize);
    }
    else {
        return getDynamicMemory(intBufferSize);
    }
}
