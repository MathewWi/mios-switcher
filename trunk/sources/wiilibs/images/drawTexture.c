#include <stdlib.h>
#include "../../clibs/libshare/pngu.h"
#include "../../clibs/libgeometry/getPolyContainerPosition.h"
#include "../../clibs/libgeometry/libgeometry.h"
#include "../../clibs/macros.h"
#include "drawTexture.h"
//version finale
u64 drawTexture(const void *imgTextureRgbaData,u16 intWidth,u16 intHeight,u16 intTileLeft,u16 intTileTop,u16 intTileWidth,u16 intTileHeight,s16 *intDestLeft,s16 *intDestTop,u16 intFbWidth,u16 intFbHeight,u16 intDrawingLayerLeft,u16 intDrawingLayerTop,u16 intDrawingLayerWidth,u16 intDrawingLayerHeight,void *framebuffer) {
PNGU_u8 *imgTexture;
PNGU_u32 *fbPixel;
double dbPolyPoints[2]={0,0};
u64 varout=0;
    if ((intTileLeft<intWidth) && (intTileTop<intHeight)) {
        intHeight=intHeight-intTileTop;
        intTileHeight=MIN(intTileHeight,intHeight);
        intHeight=intDrawingLayerTop+intDrawingLayerHeight;
        switch(*intDestTop) {
            case ALIGN_TOP:
            case ALIGN_MIDDLE:
            case ALIGN_BOTTOM:
                dbPolyPoints[1]=intTileHeight;
                if ((*intDestTop=ROUND(getPolyContainerPosition(dbPolyPoints,2,intDrawingLayerTop,intHeight,*intDestTop)))<intDrawingLayerTop) {
                    intTileTop=intTileTop+intDrawingLayerTop-*intDestTop;
                    *intDestTop=0;
                }
                break;
            default:
                *intDestTop=abs(*intDestTop);
                break;
        }
        if ((*intDestTop=*intDestTop+intDrawingLayerTop)<intHeight) {
            intHeight=intHeight-*intDestTop;
            intTileHeight=MIN(intTileHeight,intHeight);
            intHeight=intWidth-intTileLeft;
            intTileWidth=MIN(intTileWidth,intHeight);
            intHeight=intDrawingLayerLeft+intDrawingLayerWidth;
            switch(*intDestLeft) {
                case ALIGN_LEFT:
                case ALIGN_CENTER:
                case ALIGN_RIGHT:
                    dbPolyPoints[1]=intTileWidth;
                    if ((*intDestLeft=ROUND(getPolyContainerPosition(dbPolyPoints,2,intDrawingLayerLeft,intHeight,*intDestLeft)))<intDrawingLayerLeft) {
                        intTileLeft=intTileLeft+intDrawingLayerLeft-*intDestLeft;
                        *intDestLeft=0;
                    }
                    break;
                default:
                    *intDestLeft=abs(*intDestLeft);
                    break;
            }
            if ((*intDestLeft=*intDestLeft+intDrawingLayerLeft)<intHeight) {
                intHeight=intHeight-*intDestLeft;
                intTileWidth=MIN(intTileWidth,intHeight);
                if ((*intDestLeft<intFbWidth) && (*intDestTop<intFbHeight)) {
                    intHeight=intFbHeight-*intDestTop;
                    intTileHeight=MIN(intTileHeight,intHeight);
                    intHeight=intFbWidth-*intDestLeft;
                    intTileWidth=MIN(intTileWidth,intHeight);
                    varout=MAJOR_MINOR_NUMBER(intTileWidth,intTileHeight,u32);
                    intTileHeight=intTileHeight+intTileTop;
                    intTileWidth=intTileWidth/2;
                    intFbWidth=intFbWidth/2;
                    fbPixel=(PNGU_u32 *) framebuffer+*intDestTop*intFbWidth+*intDestLeft/2;
                    while (intTileTop<intTileHeight) {
                        imgTexture=(PNGU_u8 *) imgTextureRgbaData+(intTileTop*intWidth+intTileLeft)*4;
                        for (intHeight=0;intHeight<intTileWidth;intHeight++) {
                            fbPixel[intHeight]=PNGU_RGB8_TO_YCbYCr(imgTexture[0],imgTexture[1],imgTexture[2],imgTexture[4],imgTexture[5],imgTexture[6]);
                            imgTexture=imgTexture+8;
                        }
                        fbPixel=fbPixel+intFbWidth;
                        intTileTop++;
                    }
                }
            }
        }
    }
    return varout;
}
