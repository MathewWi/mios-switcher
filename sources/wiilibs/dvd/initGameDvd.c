#include <string.h>
#include <ogc/ipc.h>
#include <gctypes.h>
#include "../system/system.h"
#include "stopDvd.h"
#include <stdlib.h>
#include "resetDvd.h"
#include "readDvdDiscId.h"
#include "initDvd.h"
#include "dvd.h"
#include "initGameDvd.h"
extern u32 intIoctlInputBuffer[8] __attribute__((aligned(0x20)));
extern u32 intIoctlOutputBuffer[8] __attribute__((aligned(0x20)));
extern s32 intDiFd;
dvddiskid *initGameDvd() {
static dvddiskid *varout;
    if (initDvd()) {
        if (resetDvd()) {
            if ((varout=readDvdDiscId())!=NULL) {
                memset(intIoctlInputBuffer,0,IOCTL_BUFFER_SIZE);
                intIoctlInputBuffer[0]=IOCTL_DI_DVDLowAudioBufferConfig << 24;
                if (varout->streaming) {
                    intIoctlInputBuffer[1]=1;
                    if (varout->streambufsize) {
                        intIoctlInputBuffer[2]=10;
                    }
                }
                IOS_Ioctl(intDiFd,IOCTL_DI_DVDLowAudioBufferConfig,intIoctlInputBuffer,IOCTL_BUFFER_SIZE,intIoctlOutputBuffer,IOCTL_BUFFER_SIZE);
                return varout;
            }
        }
        stopDvd();
    }
	return NULL;
}
