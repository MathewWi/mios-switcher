#include <ogc/gx_struct.h>
#include <ogc/video_types.h>
#include "getGameVideoMode.h"
GXRModeObj *getGameVideoMode(const char *strDiscID,enum VIDEO_MODES *VIDEO_MODE) {
    switch(*VIDEO_MODE) {
        case PAL50_VIDEO_MODE:
            return (GXRModeObj *) &TVPal528IntDf;
        case PAL60_VIDEO_MODE:
            return (GXRModeObj *) &TVEurgb60Hz480IntDf;
        case NTSC480I_VIDEO_MODE:
            return (GXRModeObj *) &TVNtsc480IntDf;
        case NTSC480P_VIDEO_MODE:
        case PATCHED_NTSC480P_VIDEO_MODE:
            return (GXRModeObj *) &TVNtsc480Prog;
        case PAL480P_VIDEO_MODE:
        case PATCHED_PAL480P_VIDEO_MODE:
            return (GXRModeObj *) &TVEurgb60Hz480Prog;
        default:
            switch (strDiscID[3]) {
                case 'P':
                case 'D':
                case 'F':
                case 'S':
                case 'I':
                case 'L':
                case 'M':
                case 'X':
                case 'Y':
                    *VIDEO_MODE=PAL50_VIDEO_MODE;
                    return getGameVideoMode(strDiscID,VIDEO_MODE);
                case 'E':
                case 'J':
                case 'N':
                default:
                    *VIDEO_MODE=NTSC480I_VIDEO_MODE;
                    return getGameVideoMode(strDiscID,VIDEO_MODE);
			}
            break;
    }
}
