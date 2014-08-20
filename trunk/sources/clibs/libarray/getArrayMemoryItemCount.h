#ifndef _GETARRAYMEMORYITEMCOUNT_H_
#define _GETARRAYMEMORYITEMCOUNT_H_
#include <stdbool.h>
unsigned int getArrayMemoryItemCount(const void *varMemoryItems,unsigned int intMemoryItemsCount,unsigned int intMemoryStepSize,const void *varItem,int intItemSize,bool blnSorted,unsigned int **intMemoryItemIndexes);
#endif
