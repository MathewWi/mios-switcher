#include <stdio.h>
#include <stdlib.h>
#include "writeBinaryFile.h"
void writeBinaryFile(const char *strFileName,const void *varContent,size_t intContentSize) {
FILE *fd;
    if ((fd=fopen(strFileName,"wb"))!=NULL) {
        fwrite(varContent,intContentSize,1,fd);
        fclose(fd);
    }
}
