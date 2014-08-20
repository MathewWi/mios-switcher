#include <gctypes.h>
#include <ogc/ipc.h>
#include "stopDvdMotor.h"
extern bool isDVDReady;
extern s32 intDiFd;
void stopDvd() {
    if (isDVDReady) {
        stopDvdMotor();
        IOS_Close(intDiFd);
        isDVDReady=false;
	}
}
