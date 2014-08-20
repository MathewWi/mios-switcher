#ifndef _GETARRAYITEMCOUNT_H_
#define _GETARRAYITEMCOUNT_H_
#include <stdbool.h>
unsigned int getArrayItemCount(const void *varItems,unsigned int intItemsCount,const void *varItem,int intItemSize,bool blnSorted,unsigned int **intItemIndexes);
#endif
