#ifndef _GETARRAYMEMORYITEMINDEX_H_
#define _GETARRAYMEMORYITEMINDEX_H_
#include <stdbool.h>
unsigned int getArrayMemoryItemIndex(const void *varMemoryItems,unsigned int intMemoryItemsCount,const void *varItem,int intItemSize,unsigned int intMemoryStepSize,bool blnSorted);
#endif
