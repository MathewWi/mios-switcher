#include <stdio.h>
#include <stdlib.h>
#include "../libmemory/getAlignedBuffer.h"
#include "../libmemory/freeVector.h"
#include "../macros.h"
#include "getFileSize2.h"
#include "getFileContent.h"
//version finale
void *getFileContent(const char *strFileName,size_t *intFileSize,size_t intAlignedBufferBlockSize) {
FILE *fd;
void *varout=NULL;
long lngFileSize;
    if ((fd=fopen(strFileName,"rb"))==NULL) {
        *intFileSize=0;
    }
    else {
        lngFileSize=getFileSize2(fd);
        if ((*intFileSize=MAX(lngFileSize,0))>0) {
            if (!fseek(fd,0,SEEK_SET)) {
                if ((varout=getAlignedBuffer(*intFileSize,intAlignedBufferBlockSize))!=NULL) {
                    if (fread(varout,*intFileSize,1,fd)!=1) {
                        freeVector(&varout);
                    }
                }
            }
        }
        fclose(fd);
    }
    return varout;
}
