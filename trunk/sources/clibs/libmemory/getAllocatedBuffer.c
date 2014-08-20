#include <string.h>
#include <stdlib.h>
#include "../macros.h"
#include "getAlignedBuffer.h"
#include "getAllocatedBuffer.h"
//version finale
void *getAllocatedBuffer(size_t intBufferSize,size_t intBlockSize,unsigned int intInitOffset,size_t intInitSize,unsigned char chInitValue) {
void *varout=NULL;
    if ((varout=getAlignedBuffer(intBufferSize,intBlockSize))==NULL) {
        //todo
    }
    else {
        intBufferSize=(intBlockSize)?CEIL(intBufferSize,intBlockSize):intBufferSize;
        if (intInitOffset<intBufferSize) {
            intBufferSize=intBufferSize-intInitOffset;
            memset(varout+intInitOffset,chInitValue,MIN(intBufferSize,intInitSize));
        }
    }
    return varout;
}
