#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/libshare/pngu.h"
#include "freePngTexture.h"
void freePngTexture(struct stPngTexture *stTexture) {
    PNGU_ReleaseImageContext(stTexture->imgContext);
    freeVector(&stTexture->imgRgbaData);
}
