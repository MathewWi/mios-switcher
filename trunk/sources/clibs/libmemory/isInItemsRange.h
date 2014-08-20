#ifndef _ISINITEMSRANGE_H_
#define _ISINITEMSRANGE_H_
#include <stdbool.h>
signed char isInItemsRange(const void *varItem,const void *varMinItem,const void *varMaxItem,int intItemSize,bool blnIncludeMinRange,bool blnIncludeMaxRange);
#endif
