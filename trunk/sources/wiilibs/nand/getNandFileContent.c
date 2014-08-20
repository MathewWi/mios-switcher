#include <stdlib.h>
#include <ogc/isfs.h>
#include "../../clibs/libmemory/getAllocatedBuffer.h"
#include "../../clibs/libmemory/freeVector.h"
#include "getNandFileSize.h"
#include "getNandFileContent.h"
//version finale
void *getNandFileContent(const char *strNandFileName,size_t *intNandFileSize) {
void *varout=NULL;
s32 intFd,intReturnValue;
    *intNandFileSize=0;
    if ((intFd=ISFS_Open(strNandFileName,ISFS_OPEN_READ))<0) {
        //TODO
    }
    else {
        if ((intReturnValue=getNandFileSize(intFd))>0) {
            if ((varout=getAllocatedBuffer(intReturnValue,32,0,-1,0))==NULL) {
                //TODO
            }
            else {
                if ((intReturnValue=ISFS_Read(intFd,varout,intReturnValue))<0) {
                    //TODO
                    freeVector(&varout);
                }
                else {
                    *intNandFileSize=intReturnValue;
                }
            }
        }
        else {
            //TODO
        }
        ISFS_Close(intFd);
    }
    return varout;
}
