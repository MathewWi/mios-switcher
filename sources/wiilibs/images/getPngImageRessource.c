#include <stddef.h>
#include <stdlib.h>
#include "getPngImageRessource.h"
//version finale
IMGCTX getPngImageRessource(const void *imgData,PNGUPROP *imgProperties) {
IMGCTX varout;
    if ((varout=PNGU_SelectImageFromBuffer(imgData))) {
        if (PNGU_GetImageProperties(varout,imgProperties)!=PNGU_OK) {
            PNGU_ReleaseImageContext(varout);
            varout=NULL;
        }
	}
    return varout;
}
