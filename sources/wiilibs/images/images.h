#ifndef _IMAGES_H_
#define _IMAGES_H_
#include "../../clibs/libshare/pngu.h"
struct stPixelLocation {
    short int intLeft;
    short int intTop;
};
struct stPngTexture {
    IMGCTX imgContext;
    void *imgRgbaData;
    PNGUPROP imgProperties;
};
struct stTileTexture {
    const void *imgTextureData;
    unsigned int intTileLeft;
    unsigned int intTileTop;
    unsigned int intTileWidth;
    unsigned int intTileHeight;
};
struct stTextureSettings {
    struct stTileTexture stTileTextureSettings;
    struct stPixelLocation stTextureLocationSettings;
};
#endif
