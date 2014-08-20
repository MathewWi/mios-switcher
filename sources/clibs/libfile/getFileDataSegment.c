#include <stdlib.h>
#include "../libmemory/getAlignedBuffer.h"
#include "../libmemory/libmemory.h"
#include "../libmemory/freeVector.h"
#include "readFileDataSegment.h"
#include "getFileDataSegment.h"
//version finale
void *getFileDataSegment(FILE *fp,unsigned int intOffset,size_t *intDataSize,int intOffsetOrigin,size_t intAlignedBufferBlockSize) {
void *varout=NULL;
    if ((varout=getAlignedBuffer(*intDataSize,intAlignedBufferBlockSize))!=NULL) {
        if ((intOffset=readFileDataSegment(fp,intOffset,*intDataSize,intOffsetOrigin,varout))==0) {
            freeVector(&varout);
        }
        else if (*intDataSize>intOffset) {
            varout=REALLOC_ALIGNED_BUFFER(&varout,intOffset,intAlignedBufferBlockSize);
        }
        *intDataSize=intOffset;
    }
    return varout;
}
