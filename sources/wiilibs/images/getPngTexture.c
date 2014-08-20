#include <malloc.h>
#include <stdlib.h>
#include "../../clibs/libshare/pngu.h"
#include "getPngImageRessource.h"
#include "getPngTexture.h"
bool getPngTexture(const void *imgData,struct stPngTexture *stTexture) {
    if ((stTexture->imgContext=getPngImageRessource(imgData,&stTexture->imgProperties))) {
        if ((stTexture->imgRgbaData=malloc(4*stTexture->imgProperties.imgWidth*stTexture->imgProperties.imgHeight))==NULL) {
            PNGU_ReleaseImageContext(stTexture->imgContext);
        }
        else {
            PNGU_DECODE_TO_COORDS_RGBA8(stTexture->imgContext,0,0,stTexture->imgProperties.imgWidth,stTexture->imgProperties.imgHeight,255,stTexture->imgProperties.imgWidth,stTexture->imgProperties.imgHeight,stTexture->imgRgbaData);
            return true;
        }
    }
    return false;
}
