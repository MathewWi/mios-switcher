#include <string.h>
#include <di/di.h>
#include <ogc/ipc.h>
#include <gctypes.h>
#include "../system/system.h"
#include "isDvdReady.h"
#include "resetDvd.h"
extern u32 intIoctlInputBuffer[8] __attribute__((aligned(0x20)));
extern u32 intIoctlOutputBuffer[8] __attribute__((aligned(0x20)));
extern s32 intDiFd;
bool resetDvd() {
    if (isDvdReady()) {
        memset(intIoctlInputBuffer,0,IOCTL_BUFFER_SIZE);
		intIoctlInputBuffer[0]=DVD_RESET<<24;
		intIoctlInputBuffer[1]=1;
		return (IOS_Ioctl(intDiFd,DVD_RESET,intIoctlInputBuffer,IOCTL_BUFFER_SIZE,intIoctlOutputBuffer,IOCTL_BUFFER_SIZE)==1);
    }
    return false;
}
