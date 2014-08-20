#include <stdlib.h>
#include "../libmemory/freeVector.h"
#include "getFileDataSegment.h"
#include "getFileDataSegment2.h"
//version finale
void *getFileDataSegment2(FILE *fp,unsigned int intOffset,size_t intDataSize,int intOffsetOrigin,size_t intAlignedBufferBlockSize) {
void *varout=NULL;
size_t intExpectedDataSize=intDataSize;
    if ((varout=getFileDataSegment(fp,intOffset,&intDataSize,intOffsetOrigin,intAlignedBufferBlockSize))!=NULL) {
        if (intExpectedDataSize!=intDataSize) {
            freeVector(&varout);
        }
    }
    return varout;
}
