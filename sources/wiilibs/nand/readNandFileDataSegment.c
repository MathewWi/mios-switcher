#include <ogc/isfs.h>
#include "readNandFileDataSegment.h"
//version finale
size_t readNandFileDataSegment(s32 intFd,unsigned int intOffset,size_t intDataSize,int intOffsetOrigin,void *varAlignedDataBlock) {
    if (intDataSize) {
        if ((intOffsetOrigin=ISFS_Seek(intFd,intOffset,intOffsetOrigin))<0) {
            intDataSize=0;
        }
        else {
            if ((intOffsetOrigin=ISFS_Read(intFd,varAlignedDataBlock,intDataSize))<0) {
                intDataSize=0;
            }
            else {
                intDataSize=intOffsetOrigin;
            }
        }
    }
    return intDataSize;
}
