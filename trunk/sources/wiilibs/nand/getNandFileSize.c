#include <stdlib.h>
#include <ogc/isfs.h>
#include "../../clibs/libmemory/libmemory.h"
#include "../../clibs/libmemory/freeVector.h"
#include "getNandFileSize.h"
//version finale
s32 getNandFileSize(s32 intFd) {
s32 varout;
fstats *fileStats=NULL;
    if ((fileStats=GET_ALIGNED_MEMORY(sizeof(fstats),32))==NULL) {
        //TODO
        varout=-1;
    }
    else {
        if ((varout=ISFS_GetFileStats(intFd,fileStats))<0) {
            //TODO
        }
        else {
            varout=fileStats->file_length;
        }
        freeVector((void **) &fileStats);
    }
    return varout;
}
