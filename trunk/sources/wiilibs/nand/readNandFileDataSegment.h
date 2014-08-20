#ifndef _READNANDFILEDATASEGMENT_H_
#define _READNANDFILEDATASEGMENT_H_
#include <stddef.h>
#include <gctypes.h>
size_t readNandFileDataSegment(s32 intFd,unsigned int intOffset,size_t intDataSize,int intOffsetOrigin,void *varAlignedDataBlock);
#endif
