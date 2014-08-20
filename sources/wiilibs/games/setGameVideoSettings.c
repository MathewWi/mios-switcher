#include "../mios/mios.h"
#include "setGameVideoSettings.h"
void setGameVideoSettings(struct stGameConfig *stGameSettings,enum VIDEO_MODES VIDEO_MODE) {
    switch (VIDEO_MODE) {
        case PAL50_VIDEO_MODE:
            stGameSettings->stDiosMiosConfig.intVideoMode=((stGameSettings->stDiosMiosConfig.intVideoMode>>16)<<16) | (DIOS_MIOS_VIDEO_FORCE_PAL50*(stGameSettings->stDiosMiosConfig.intVideoMode & DIOS_MIOS_VIDEO_FORCE)/DIOS_MIOS_VIDEO_FORCE);
            break;
        case PAL60_VIDEO_MODE:
            stGameSettings->stDiosMiosConfig.intVideoMode=((stGameSettings->stDiosMiosConfig.intVideoMode>>16)<<16) | (DIOS_MIOS_VIDEO_FORCE_PAL60*(stGameSettings->stDiosMiosConfig.intVideoMode & DIOS_MIOS_VIDEO_FORCE)/DIOS_MIOS_VIDEO_FORCE);
            break;
        case NTSC480I_VIDEO_MODE:
            stGameSettings->stDiosMiosConfig.intVideoMode=((stGameSettings->stDiosMiosConfig.intVideoMode>>16)<<16) | (DIOS_MIOS_VIDEO_FORCE_NTSC*(stGameSettings->stDiosMiosConfig.intVideoMode & DIOS_MIOS_VIDEO_FORCE)/DIOS_MIOS_VIDEO_FORCE);
            break;
        case NTSC480P_VIDEO_MODE:
        case PATCHED_NTSC480P_VIDEO_MODE:
            stGameSettings->stDiosMiosConfig.intVideoMode=((stGameSettings->stDiosMiosConfig.intVideoMode>>16)<<16) | (DIOS_MIOS_VIDEO_PROGRESSIVE_PATCH*(VIDEO_MODE-NTSC480P_VIDEO_MODE)/2) | (DIOS_MIOS_VIDEO_FORCE_PROGRESSIVE*(stGameSettings->stDiosMiosConfig.intVideoMode & DIOS_MIOS_VIDEO_FORCE)/DIOS_MIOS_VIDEO_FORCE);
            break;
        case PAL480P_VIDEO_MODE:
        case PATCHED_PAL480P_VIDEO_MODE:
            stGameSettings->stDiosMiosConfig.intVideoMode=((stGameSettings->stDiosMiosConfig.intVideoMode>>16)<<16) | (DIOS_MIOS_VIDEO_PROGRESSIVE_PATCH*(VIDEO_MODE-PAL480P_VIDEO_MODE)/2) | (DIOS_MIOS_VIDEO_FORCE_PROGRESSIVE*(stGameSettings->stDiosMiosConfig.intVideoMode & DIOS_MIOS_VIDEO_FORCE)/DIOS_MIOS_VIDEO_FORCE);
            break;
        default:
            switch (stGameSettings->strDiscID[3]) {
                case 'P':
                case 'D':
                case 'F':
                case 'S':
                case 'I':
                case 'L':
                case 'M':
                case 'X':
                case 'Y':
                    setGameVideoSettings(stGameSettings,PAL50_VIDEO_MODE);
                    break;
                case 'E':
                case 'J':
                case 'N':
                default:
                    setGameVideoSettings(stGameSettings,NTSC480I_VIDEO_MODE);
                    break;
			}
            break;
    }
}
