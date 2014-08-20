#ifndef _APPLYONTHEFLYIOSPATCHS_H_
#define _APPLYONTHEFLYIOSPATCHS_H_
#include <stddef.h>
#include <gctypes.h>
unsigned int applyOnTheFlyIosPatchs(u8 *pStartPatchScanAddress,u8 *pEndPatchScanAddress,const u8 *chOriginalBytes,size_t chOriginalBytesCount,const u8 *chNewBytes,size_t chNewBytesCount,unsigned int intOffsetPatch);
#endif
