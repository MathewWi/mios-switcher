#include <ogc/video.h>
#include "setFrameBuffer.h"
//version finale
void setFrameBuffer(GXRModeObj *objRenderSettings,void *frameBuffer) {
    VIDEO_SetNextFramebuffer(frameBuffer);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (objRenderSettings->viTVMode & VI_NON_INTERLACE) {
        VIDEO_WaitVSync();
    }
}
