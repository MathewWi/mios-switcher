#include <ogc/ipc.h>
#include <gctypes.h>
#include "stopDvd.h"
#include "initDvd.h"
extern s32 intDiFd;
extern bool isDVDReady;
bool initDvd() {
    stopDvd();
    if ((intDiFd=IOS_Open("/dev/di",0))>-1) {
        isDVDReady=true;
    }
    return isDVDReady;
}
