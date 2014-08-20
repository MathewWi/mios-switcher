#ifndef _EXPANDVECTOR_H_
#define _EXPANDVECTOR_H_
#include <stddef.h>
void *expandVector(void **varVector,unsigned int intItemsCount,unsigned int intAddingItemsCount,const void *varInitItem,size_t intItemSize);
#endif
