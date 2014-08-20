#include <math.h>
#include <stdlib.h>
#include <ogc/video.h>
#include "../../clibs/macros.h"
#include "../images/drawPng.h"
#include "drawFramebuffer.h"
//version finale
u64 drawFramebuffer(const void *imgBackground,struct stTextureSettings *stTexturesSettings,unsigned char intTexturesCount,enum CONSOLE_COLORS BGCOLOR,short int *intBgLeft,short int *intBgTop,double *dbBgXScalingFactor,double *dbBgYScalingFactor,GXRModeObj *objRenderSettings,void *frameBuffer) {
u64 varout;
double dbTempVar;
    VIDEO_ClearFrameBuffer(objRenderSettings,frameBuffer,BGCOLOR);
    if (((*dbBgXScalingFactor=fabs(*dbBgXScalingFactor))==0) || ((*dbBgYScalingFactor=fabs(*dbBgYScalingFactor))==0)) {
        if (imgBackground==NULL) {
            *dbBgXScalingFactor=(*dbBgXScalingFactor==0)+*dbBgXScalingFactor;
            *dbBgYScalingFactor=(*dbBgYScalingFactor==0)+*dbBgYScalingFactor;
        }
        else {
            *dbBgXScalingFactor=(*dbBgXScalingFactor==0)*(double) objRenderSettings->fbWidth/(double) PNG_WIDTH(imgBackground)+*dbBgXScalingFactor;
            *dbBgYScalingFactor=(*dbBgYScalingFactor==0)*(double) objRenderSettings->xfbHeight/(double) PNG_HEIGHT(imgBackground)+*dbBgYScalingFactor;
        }
    }
    else {
        dbTempVar=(double) objRenderSettings->fbWidth/(double) PNG_WIDTH(imgBackground);
        *dbBgXScalingFactor=MIN(*dbBgXScalingFactor,dbTempVar);
        dbTempVar=(double) objRenderSettings->xfbHeight/(double) PNG_HEIGHT(imgBackground);
        *dbBgYScalingFactor=MIN(*dbBgYScalingFactor,dbTempVar);

    }
    varout=drawPng(imgBackground,0,0,0,0,intBgLeft,intBgTop,*dbBgXScalingFactor,*dbBgYScalingFactor,objRenderSettings->fbWidth,objRenderSettings->xfbHeight,0,0,objRenderSettings->fbWidth,objRenderSettings->xfbHeight,frameBuffer);
    while (intTexturesCount) {
        intTexturesCount--;
        drawPng(stTexturesSettings[intTexturesCount].stTileTextureSettings.imgTextureData,stTexturesSettings[intTexturesCount].stTileTextureSettings.intTileLeft,stTexturesSettings[intTexturesCount].stTileTextureSettings.intTileTop,stTexturesSettings[intTexturesCount].stTileTextureSettings.intTileWidth,stTexturesSettings[intTexturesCount].stTileTextureSettings.intTileHeight,&stTexturesSettings[intTexturesCount].stTextureLocationSettings.intLeft,&stTexturesSettings[intTexturesCount].stTextureLocationSettings.intTop,*dbBgXScalingFactor,*dbBgYScalingFactor,objRenderSettings->fbWidth,objRenderSettings->xfbHeight,varout?*intBgLeft:0,varout?*intBgTop:0,varout?MAJOR_NUMBER(varout,u32):objRenderSettings->fbWidth,varout?MINOR_NUMBER(varout,u32):objRenderSettings->xfbHeight,frameBuffer);
    }
    return varout;
}
