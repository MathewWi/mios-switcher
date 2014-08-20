#ifndef _GETFILEDATASEGMENT_H_
#define _GETFILEDATASEGMENT_H_
#include <stdio.h>
#include <stddef.h>
void *getFileDataSegment(FILE *fp,unsigned int intOffset,size_t *intDataSize,int intOffsetOrigin,size_t intAlignedBufferBlockSize);
#endif
