#include <string.h>
#include <ogc/cache.h>
#include "setCacheDataSegment.h"
void setCacheDataSegment(void *varCacheDataSegment,size_t intDataSegmentSize,void *varNewData) {
    memcpy(varCacheDataSegment,varNewData,intDataSegmentSize);
    DCFlushRange(varCacheDataSegment,intDataSegmentSize);
}
