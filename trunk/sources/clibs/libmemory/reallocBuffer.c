#include <malloc.h>
#include <stdlib.h>
#include "freeVector.h"
#include "libmemory.h"
#include "reallocBuffer.h"
void *reallocBuffer(void **varBuffer,size_t intBufferSize,size_t intBlockSize) {
void *varNewBuffer=NULL;
    if (intBufferSize) {
        if (intBlockSize) {
            varNewBuffer=REALLOC_ALIGNED_BUFFER(varBuffer,intBufferSize,intBlockSize);
        }
        else {
            varNewBuffer=realloc(*varBuffer,intBufferSize);
        }
        if (varNewBuffer!=NULL) {
            *varBuffer=varNewBuffer;
        }
    }
    else {
        freeVector((void **) varBuffer);
    }
    return varNewBuffer;
}
