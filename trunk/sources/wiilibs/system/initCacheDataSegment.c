#include <string.h>
#include <ogc/cache.h>
#include "initCacheDataSegment.h"
void initCacheDataSegment(void *varCacheDataSegment,size_t intDataSegmentSize,unsigned char chInitValue) {
    memset(varCacheDataSegment,chInitValue,intDataSegmentSize);
    DCFlushRange(varCacheDataSegment,intDataSegmentSize);
}
