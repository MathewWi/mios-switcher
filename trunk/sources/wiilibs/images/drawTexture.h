#ifndef _DRAWTEXTURE_H_
#define _DRAWTEXTURE_H_
#include <gctypes.h>
u64 drawTexture(const void *imgTextureRgbaData,u16 intWidth,u16 intHeight,u16 intTileLeft,u16 intTileTop,u16 intTileWidth,u16 intTileHeight,s16 *intDestLeft,s16 *intDestTop,u16 intFbWidth,u16 intFbHeight,u16 intDrawingLayerLeft,u16 intDrawingLayerTop,u16 intDrawingLayerWidth,u16 intDrawingLayerHeight,void *framebuffer);
#endif
