#include <string.h>
#include <stdlib.h>
#include "getAlignedBuffer.h"
#include "getClonedBuffer.h"
void *getClonedBuffer(void *chBuffer,size_t intBufferSize,size_t intBlockSize) {
void *varout=NULL;
    if (chBuffer!=NULL) {
        if ((varout=getAlignedBuffer(intBufferSize,intBlockSize))==NULL) {
            //TODO
        }
        else {
            memcpy(varout,chBuffer,intBufferSize);
        }
    }
    return varout;
}
