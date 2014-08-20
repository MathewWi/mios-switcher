#ifndef _GETFILEDATASEGMENT2_H_
#define _GETFILEDATASEGMENT2_H_
#include <stdio.h>
#include <stddef.h>
void *getFileDataSegment2(FILE *fp,unsigned int intOffset,size_t intDataSize,int intOffsetOrigin,size_t intAlignedBufferBlockSize);
#endif
