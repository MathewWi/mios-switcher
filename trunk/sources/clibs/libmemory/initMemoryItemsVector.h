#ifndef _INITMEMORYITEMSVECTOR_H_
#define _INITMEMORYITEMSVECTOR_H_
#include <stddef.h>
void *initMemoryItemsVector(void **varMemoryItemsVector,unsigned int intItemsCount,size_t intMemoryStepSize,size_t intItemSize,const void *varInitItem);
#endif
