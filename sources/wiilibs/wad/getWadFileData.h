#ifndef _GETWADFILEDATA_H_
#define _GETWADFILEDATA_H_
#include <stdio.h>
#include <stddef.h>
#include "wad.h"
void *getWadFileData(FILE *fpwad,struct stWadMap *stWadFileMap,int intWadData,size_t *intDataSize,size_t intAlignedBufferBlockSize);
#endif
