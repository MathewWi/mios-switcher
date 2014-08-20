#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <gctypes.h>
#include <ogc/video.h>
#include <ogc/system.h>
#include "../../main.h"
#include "../../clibs/libgeometry/getPolyContainerPosition.h"
#include "../../clibs/libgeometry/libgeometry.h"
#include "../../clibs/macros.h"
#include "../video/drawFramebuffer.h"
#include "../gui/printAlignedText.h"
#include "resetDefaultFontStyle.h"
#include "setFrameBuffer.h"
#include "initConsole.h"
#ifdef DEBUG_FILE
#include <ogc/video_types.h>
#include "../../clibs/libdebug/libdebug.h"
#include "../../clibs/libdebug/setDebugMessage.h"
#endif
//version finale
GXRModeObj *initConsole(enum CONSOLE_COLORS CONSOLE_COLOR,const char *strSplashScreenMessage,struct stVideoSettings *stVideoParameters) {
GXRModeObj *varout=NULL;
double dbPolyPoints[2],dbReferenceWidth,dbReferenceHeight;
struct stConsoleCursorLocation stTexteLocation;
u64 intMajorMinorBgDimensions;
    VIDEO_Init();
    varout=VIDEO_GetPreferredMode(NULL);
#ifdef DEBUG_FILE
    setDebugMessage(DEBUG_LOG_MESSAGE,0,__FILE__,__LINE__,"viTVMode=%u, fbWidth=%u, efbHeight=%u, xfbHeight=%u, viXOrigin=%u, viYOrigin=%u, viWidth=%u, viHeight=%u",varout->viTVMode,varout->fbWidth,varout->efbHeight,varout->xfbHeight,varout->viXOrigin,varout->viYOrigin,varout->viWidth,varout->viHeight);
#endif
    VIDEO_Configure(varout);
    stVideoParameters->stFrameBuffers[0].frameBuffer=MEM_K0_TO_K1(SYS_AllocateFramebuffer(varout));
    setFrameBuffer(varout,stVideoParameters->stFrameBuffers[0].frameBuffer);
    stVideoParameters->intBgWidth=stVideoParameters->intBgLeft;
    stVideoParameters->intBgHeight=stVideoParameters->intBgTop;
    intMajorMinorBgDimensions=drawFramebuffer(stVideoParameters->imgBgData,stVideoParameters->stFrameBuffers[0].stTexturesSettings,STATIC_ARRAY_SIZE(stVideoParameters->stFrameBuffers[0].stTexturesSettings),CONSOLE_COLOR,&stVideoParameters->intBgLeft,&stVideoParameters->intBgTop,&stVideoParameters->dbBgImgXScaleFactor,&stVideoParameters->dbBgImgYScaleFactor,varout,stVideoParameters->stFrameBuffers[0].frameBuffer);
    if (intMajorMinorBgDimensions) {
        dbReferenceWidth=PNG_WIDTH(stVideoParameters->imgBgData);
        dbReferenceHeight=PNG_HEIGHT(stVideoParameters->imgBgData);
    }
    else {
        dbReferenceWidth=varout->fbWidth;
        dbReferenceHeight=varout->xfbHeight;
    }
    if ((stVideoParameters->dbConsoleWidth=fabs(stVideoParameters->dbConsoleWidth))<=1) {
        stVideoParameters->dbConsoleWidth=stVideoParameters->dbConsoleWidth*dbReferenceWidth;
        dbPolyPoints[0]=0;
        dbPolyPoints[1]=stVideoParameters->dbConsoleWidth;
    }
    else {
        dbPolyPoints[0]=stVideoParameters->dbConsoleLeft;
        dbPolyPoints[1]=stVideoParameters->dbConsoleLeft;
    }
    stVideoParameters->dbConsoleLeft=(s32) ROUND(stVideoParameters->dbBgImgXScaleFactor*getPolyContainerPosition(dbPolyPoints,2,0,dbReferenceWidth,stVideoParameters->dbConsoleLeft))+stVideoParameters->intBgLeft;
    if ((stVideoParameters->dbConsoleHeight=fabs(stVideoParameters->dbConsoleHeight))<=1) {
        stVideoParameters->dbConsoleHeight=stVideoParameters->dbConsoleHeight*dbReferenceHeight;
        dbPolyPoints[0]=0;
        dbPolyPoints[1]=stVideoParameters->dbConsoleHeight;
    }
    else {
        dbPolyPoints[0]=stVideoParameters->dbConsoleTop;
        dbPolyPoints[1]=stVideoParameters->dbConsoleTop;
    }
    stVideoParameters->dbConsoleTop=(s32) ROUND(stVideoParameters->dbBgImgYScaleFactor*getPolyContainerPosition(dbPolyPoints,2,0,dbReferenceHeight,stVideoParameters->dbConsoleTop))+stVideoParameters->intBgTop;
    stVideoParameters->dbConsoleWidth=(s32) ROUND(stVideoParameters->dbConsoleWidth*stVideoParameters->dbBgImgXScaleFactor);
    stVideoParameters->dbConsoleHeight=(s32) ROUND(stVideoParameters->dbConsoleHeight*stVideoParameters->dbBgImgYScaleFactor);
    CON_InitEx(varout,stVideoParameters->dbConsoleLeft,stVideoParameters->dbConsoleTop,stVideoParameters->dbConsoleWidth,stVideoParameters->dbConsoleHeight);
    stTexteLocation.intColumn=STATIC_ARRAY_SIZE(stVideoParameters->stFrameBuffers);
    for (stTexteLocation.intRow=1;stTexteLocation.intRow<stTexteLocation.intColumn;stTexteLocation.intRow=stTexteLocation.intRow+1) {
        stVideoParameters->stFrameBuffers[stTexteLocation.intRow].frameBuffer=MEM_K0_TO_K1(SYS_AllocateFramebuffer(varout));
        stVideoParameters->intBgLeft=stVideoParameters->intBgWidth;
        stVideoParameters->intBgTop=stVideoParameters->intBgHeight;
        intMajorMinorBgDimensions=drawFramebuffer(stVideoParameters->imgBgData,stVideoParameters->stFrameBuffers[stTexteLocation.intRow].stTexturesSettings,STATIC_ARRAY_SIZE(stVideoParameters->stFrameBuffers[stTexteLocation.intRow].stTexturesSettings),CONSOLE_COLOR,&stVideoParameters->intBgLeft,&stVideoParameters->intBgTop,&stVideoParameters->dbBgImgXScaleFactor,&stVideoParameters->dbBgImgYScaleFactor,varout,stVideoParameters->stFrameBuffers[stTexteLocation.intRow].frameBuffer);
        setFrameBuffer(varout,stVideoParameters->stFrameBuffers[0].frameBuffer);
        CON_InitEx(varout,stVideoParameters->dbConsoleLeft,stVideoParameters->dbConsoleTop,stVideoParameters->dbConsoleWidth,stVideoParameters->dbConsoleHeight);
    }
    stVideoParameters->intBgWidth=MAJOR_NUMBER(intMajorMinorBgDimensions,u32);
    stVideoParameters->intBgHeight=MINOR_NUMBER(intMajorMinorBgDimensions,u32);
    resetDefaultFontStyle();
    if (*strSplashScreenMessage) {
        CON_GetMetrics(&stTexteLocation.intColumn,&stTexteLocation.intRow);
        printAlignedText(ALIGN_CENTER,ALIGN_MIDDLE,0,0,stTexteLocation.intRow-1,stTexteLocation.intColumn-1,true,true,&stTexteLocation,strSplashScreenMessage);
    }
    return varout;
}
