#ifndef _GETALLOCATEDBUFFER_H_
#define _GETALLOCATEDBUFFER_H_
#include <stddef.h>
void *getAllocatedBuffer(size_t intBufferSize,size_t intBlockSize,unsigned int intInitOffset,size_t intInitSize,unsigned char chInitValue);
#endif
