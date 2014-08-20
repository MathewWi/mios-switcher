#include <string.h>
#include <stdlib.h>
#include <gctypes.h>
#include <ogc/ipc.h>
#include <di/di.h>
#include "../system/system.h"
#include "isDvdReady.h"
#include "getDvdDriveInfos.h"
extern u32 intIoctlInputBuffer[8] __attribute__((aligned(0x20)));
extern s32 intDiFd;
dvddrvinfo *getDvdDriveInfos() {
static dvddrvinfo varout __attribute__((aligned(0x20)));
    if (isDvdReady()) {
        memset(intIoctlInputBuffer,0,IOCTL_BUFFER_SIZE);
        intIoctlInputBuffer[0]=DVD_IDENTIFY << 24;
        if (IOS_Ioctl(intDiFd,DVD_IDENTIFY,intIoctlInputBuffer,IOCTL_BUFFER_SIZE,&varout,sizeof(varout))==1) {
            return &varout;
        }
    }
    return NULL;
}
