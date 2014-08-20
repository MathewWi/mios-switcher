#include <stdlib.h>
#include "../../clibs/libgeometry/libgeometry.h"
#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/libmath/isInRange.h"
#include "../../clibs/libshare/pngu.h"
#include "../../clibs/macros.h"
#include "freePngTexture.h"
#include "getTileTexture.h"
#include "getPngTexture.h"
#include "resizeTexture.h"
#include "drawTexture.h"
#include "images.h"
#include "drawPng.h"
//version finale
u64 drawPng(const void *imgData,u16 intLeft,u16 intTop,u16 intWidth,u16 intHeight,s16 *intDestLeft,s16 *intDestTop,double dbXScalingFactor,double dbYScalingFactor,u16 intFbWidth,u16 intFbHeight,u16 intDrawingLayerLeft,u16 intDrawingLayerTop,u16 intDrawingLayerWidth,u16 intDrawingLayerHeight,void *framebuffer) {
struct stPngTexture stTexture;
void *imgTileTexture;
unsigned int intU32Width,intU32Height;
u64 varout=0;
    if (getPngTexture(imgData,&stTexture)) {
        if (isInRange(*intDestLeft,ALIGN_NONE,0,false,false)) {
            *intDestLeft=ROUND((double) abs(*intDestLeft)*dbXScalingFactor);
        }
        if (isInRange(*intDestTop,ALIGN_NONE,0,false,false)) {
            *intDestTop=ROUND((double) abs(*intDestTop)*dbYScalingFactor);
        }
        if ((*intDestTop<intFbHeight) && (*intDestLeft<intFbWidth)) {
            intWidth=(intWidth)?intWidth:stTexture.imgProperties.imgWidth;
            intHeight=(intHeight)?intHeight:stTexture.imgProperties.imgHeight;
            if ((dbXScalingFactor!=1) || (dbYScalingFactor!=1)) {
                intU32Width=intWidth;
                intU32Height=intHeight;
                if ((imgTileTexture=getTileTexture(stTexture.imgRgbaData,stTexture.imgProperties.imgWidth,stTexture.imgProperties.imgHeight,intLeft,intTop,&intU32Width,&intU32Height))!=NULL) {
                    intWidth=ROUND((double) intU32Width*dbXScalingFactor);
                    intHeight=ROUND((double) intU32Height*dbYScalingFactor);
                    if (imgTileTexture==stTexture.imgRgbaData) {
                        if ((stTexture.imgRgbaData=resizeTexture(&stTexture.imgRgbaData,intU32Width,intU32Height,intWidth,intHeight))!=NULL) {
                            varout=drawTexture(stTexture.imgRgbaData,intWidth,intHeight,0,0,intWidth,intHeight,intDestLeft,intDestTop,intFbWidth,intFbHeight,intDrawingLayerLeft,intDrawingLayerTop,intDrawingLayerWidth,intDrawingLayerHeight,framebuffer);
                        }
                    }
                    else {
                        if ((imgTileTexture=resizeTexture(&imgTileTexture,intU32Width,intU32Height,intWidth,intHeight))!=NULL) {
                            varout=drawTexture(imgTileTexture,intWidth,intHeight,0,0,intWidth,intHeight,intDestLeft,intDestTop,intFbWidth,intFbHeight,intDrawingLayerLeft,intDrawingLayerTop,intDrawingLayerWidth,intDrawingLayerHeight,framebuffer);
                        }
                        freeVector(&imgTileTexture);
                    }
                }
            }
            else {
                intU32Width=intDrawingLayerLeft+*intDestLeft;
                intU32Height=intDrawingLayerTop+*intDestTop;
                dbXScalingFactor=intDrawingLayerWidth+intDrawingLayerLeft;
                dbYScalingFactor=intDrawingLayerHeight+intDrawingLayerTop;
                if ((*intDestLeft>-1) && (*intDestTop>-1) && (!intLeft) && (!intTop) && (intWidth==stTexture.imgProperties.imgWidth) && (intHeight==stTexture.imgProperties.imgHeight) && (intU32Width+intWidth<=MIN(dbXScalingFactor,intFbWidth)) && (intU32Height+intHeight<=MIN(dbYScalingFactor,intFbHeight))) {
                    PNGU_DECODE_TO_COORDS_YCbYCr(stTexture.imgContext,intU32Width,intU32Height,intWidth,intHeight,intFbWidth,intFbHeight,framebuffer);
                    varout=MAJOR_MINOR_NUMBER(intWidth,intHeight,u32);
                }
                else {
                    varout=drawTexture(stTexture.imgRgbaData,stTexture.imgProperties.imgWidth,stTexture.imgProperties.imgHeight,intLeft,intTop,intWidth,intHeight,intDestLeft,intDestTop,intFbWidth,intFbHeight,intDrawingLayerLeft,intDrawingLayerTop,intDrawingLayerWidth,intDrawingLayerHeight,framebuffer);
                }
            }
        }
        freePngTexture(&stTexture);
    }
    return varout;
}
