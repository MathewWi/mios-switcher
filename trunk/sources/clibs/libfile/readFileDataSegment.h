#ifndef _READFILEDATASEGMENT_H_
#define _READFILEDATASEGMENT_H_
#include <stddef.h>
#include <stdio.h>
size_t readFileDataSegment(FILE *fp,unsigned int intOffset,size_t intDataSize,int intOffsetOrigin,void *varDataBlock);
#endif
