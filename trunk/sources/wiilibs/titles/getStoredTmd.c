#include <stdlib.h>
#include "../../clibs/libmemory/getAllocatedBuffer.h"
#include "../../clibs/libmemory/freeVector.h"
#include "../nand/haveNandAccess.h"
#include "../nand/getNandStoredTmd.h"
#include "getStoredTmd.h"
signed_blob *getStoredTmd(u64 intTitleId,size_t *intTmdSize) {
//version finale
signed_blob *varout=NULL;
s32 intReturnValue;
    if (haveNandAccess()) {
        varout=getNandStoredTmd(intTitleId,intTmdSize);
    }
    else {
        if ((intReturnValue=ES_GetStoredTMDSize(intTitleId,intTmdSize))<0) {
            //TODO
        }
        else {
            if ((varout=getAllocatedBuffer(*intTmdSize,32,0,-1,0))==NULL) {
                //TODO
            }
            else {
                if ((intReturnValue=ES_GetStoredTMD(intTitleId,varout,*intTmdSize))<0) {
                    //TODO
                    freeVector((void **) &varout);
                }
            }
        }
    }
    return varout;
}
