#ifndef _SETMEMORYITEMFUNCTIONS_H_
#define _SETMEMORYITEMFUNCTIONS_H_
#include <stddef.h>
void setMemoryItemFunctions(int intItemSize,void* (**varMemoryItem)(const void *,unsigned int,unsigned int),int (**intMemoryItemCmp)(const void *,const void *,size_t),void* (**varCurrentMemoryItem)(void **,const void *,size_t));
#endif
