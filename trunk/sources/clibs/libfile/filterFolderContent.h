#ifndef _FILTERFOLDERCONTENT_H_
#define _FILTERFOLDERCONTENT_H_
#include <stddef.h>
unsigned int filterFolderContent(char **strFolderContent,unsigned int intFolderItemsCount,const char *strFileExtension,size_t intMinFileSize,size_t intMaxFileSize);
#endif
