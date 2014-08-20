#ifndef _READDVDDATASEGMENT_H_
#define _READDVDDATASEGMENT_H_
#include <stddef.h>
#include "dvd.h"
size_t readDvdDataSegment(unsigned int intOffset,size_t intDataSize,enum DVD_READ_MODES DVD_READ_MODE,void *varAlignedDataBlock);
#endif
