#ifndef _DRAWPNG_H_
#define _DRAWPNG_H_
#include <gctypes.h>
u64 drawPng(const void *imgData,u16 intLeft,u16 intTop,u16 intWidth,u16 intHeight,s16 *intDestLeft,s16 *intDestTop,double dbXScalingFactor,double dbYScalingFactor,u16 intFbWidth,u16 intFbHeight,u16 intDrawingLayerLeft,u16 intDrawingLayerTop,u16 intDrawingLayerWidth,u16 intDrawingLayerHeight,void *framebuffer);
#endif
