#ifndef _DRAWFRAMEBUFFER_H_
#define _DRAWFRAMEBUFFER_H_
#include <gctypes.h>
#include <ogc/gx_struct.h>
#include "../images/images.h"
#include "video.h"
u64 drawFramebuffer(const void *imgBackground,struct stTextureSettings *stTexturesSettings,unsigned char intTexturesCount,enum CONSOLE_COLORS BGCOLOR,short int *intBgLeft,short int *intBgTop,double *dbBgXScalingFactor,double *dbBgYScalingFactor,GXRModeObj *objRenderSettings,void *frameBuffer);
#endif
