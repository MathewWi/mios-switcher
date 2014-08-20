#ifndef _GETDOLSLIST_H_
#define _GETDOLSLIST_H_
#include <stdbool.h>
#include <stddef.h>
#include "../menu/menu.h"
struct stListItem *getDolsList(const char *strDolsFolder,bool blnRecursive,size_t intDolMaxSize,unsigned int *intDolsCount);
#endif
