#ifndef _GETNANDFOLDERCONTENT_H_
#define _GETNANDFOLDERCONTENT_H_
#include <stdbool.h>
char **getNandFolderContent(const char *strNandFolderPath,bool blnRecursive,int *intDirectoryItemsCount);
#endif
