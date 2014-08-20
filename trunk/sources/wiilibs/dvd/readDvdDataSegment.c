#include <gctypes.h>
#include <ogc/ipc.h>
#include "../system/system.h"
#include "isDvdReady.h"
#include "readDvdDataSegment.h"
extern u32 intIoctlInputBuffer[8] __attribute__((aligned(0x20)));
extern s32 intDiFd;
size_t readDvdDataSegment(unsigned int intOffset,size_t intDataSize,enum DVD_READ_MODES DVD_READ_MODE,void *varAlignedDataBlock) {
    if (isDvdReady()) {
        if (intDataSize) {
            intIoctlInputBuffer[0]=DVD_READ_MODE << 24;
            intIoctlInputBuffer[1]=intDataSize;
            intIoctlInputBuffer[2]=intOffset >> 2;
            if (IOS_Ioctl(intDiFd,DVD_READ_MODE,intIoctlInputBuffer,IOCTL_BUFFER_SIZE,varAlignedDataBlock,intDataSize)==1) {
                return intDataSize;
            }
        }
    }
    return 0;
}
