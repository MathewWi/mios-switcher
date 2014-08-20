#ifndef _GETFILECONTENT_H_
#define _GETFILECONTENT_H_
#include <stddef.h>
void *getFileContent(const char *strFileName,size_t *intFileSize,size_t intAlignedBufferBlockSize);
#endif
