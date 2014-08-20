#ifndef _GETFOLDERCONTENT_H_
#define _GETFOLDERCONTENT_H_
#include <stdbool.h>
char **getFolderContent(const char *strFolderPath,bool blnRecursive,unsigned int *intDirectoryItemsCount);
#endif
