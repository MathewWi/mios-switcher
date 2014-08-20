#include <ogc/cache.h>
#include "initCacheDataSegment.h"
#include "initCacheCodeSegment.h"
void initCacheCodeSegment(void *varCacheCodeSegment,size_t intCodeSegmentSize,unsigned char chInitValue) {
    initCacheDataSegment(varCacheCodeSegment,intCodeSegmentSize,chInitValue);
    ICInvalidateRange(varCacheCodeSegment,intCodeSegmentSize);
}
