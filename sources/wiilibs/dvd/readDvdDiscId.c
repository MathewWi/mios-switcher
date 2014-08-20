#include <string.h>
#include <stdlib.h>
#include <ogc/ipc.h>
#include <di/di.h>
#include <gctypes.h>
#include "../system/system.h"
#include "isDvdReady.h"
#include "readDvdDiscId.h"
extern u32 intIoctlInputBuffer[8] __attribute__((aligned(0x20)));
extern s32 intDiFd;
dvddiskid *readDvdDiscId() {
static dvddiskid varout __attribute__((aligned(0x20)));
    if (isDvdReady()) {
        memset(intIoctlInputBuffer,0,IOCTL_BUFFER_SIZE);
        intIoctlInputBuffer[0]=DVD_READ_DISCID << 24;
        if (IOS_Ioctl(intDiFd,DVD_READ_DISCID,intIoctlInputBuffer,IOCTL_BUFFER_SIZE,&varout,sizeof(varout))==1) {
            return &varout;
        }
	}
    return NULL;
}
