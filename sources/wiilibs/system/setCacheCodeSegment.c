#include <ogc/cache.h>
#include "setCacheDataSegment.h"
#include "setCacheCodeSegment.h"
void setCacheCodeSegment(void *varCacheCodeSegment,size_t intCodeSegmentSize,void *varNewCode) {
    setCacheDataSegment(varCacheCodeSegment,intCodeSegmentSize,varNewCode);
    ICInvalidateRange(varCacheCodeSegment,intCodeSegmentSize);
}
