#include <string.h>
#include <stdlib.h>
#include <ogc/cache.h>
#include "applyOnTheFlyIosPatchs.h"
//version finale
unsigned int applyOnTheFlyIosPatchs(u8 *pStartPatchScanAddress,u8 *pEndPatchScanAddress,const u8 *chOriginalBytes,size_t chOriginalBytesCount,const u8 *chNewBytes,size_t chNewBytesCount,unsigned int intOffsetPatch) {
unsigned int varout=0,i,intMemoryRangeSize=(chNewBytesCount >> 5 << 5)+64;
u8 *pPatchOffset=NULL,*pPatchOffsetMemoryRange=NULL;
    while (pStartPatchScanAddress<(pEndPatchScanAddress-chNewBytesCount)) {
        if (!memcmp(pStartPatchScanAddress,chOriginalBytes,chOriginalBytesCount)) {
            varout++;
            pPatchOffset=pStartPatchScanAddress+intOffsetPatch;
            pPatchOffsetMemoryRange=(u8 *)(((u32)pPatchOffset) >> 5 << 5);
            for (i=0;i<chNewBytesCount;i++) {
                *pPatchOffset++ =chNewBytes[i];
            }
            DCFlushRange(pPatchOffsetMemoryRange,intMemoryRangeSize);
            ICInvalidateRange(pPatchOffsetMemoryRange,intMemoryRangeSize);
        }
        pStartPatchScanAddress++;
    }
    return varout;
}
