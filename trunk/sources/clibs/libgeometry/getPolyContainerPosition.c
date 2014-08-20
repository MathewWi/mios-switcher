#include <math.h>
#include "../libmemory/libmemory.h"
#include "../libarray/getArrayMinItemIndex.h"
#include "../libmath/isInRange.h"
#include "../macros.h"
#include "getAlignedPolyContainerPosition.h"
#include "libgeometry.h"
//version finale
double getPolyContainerPosition(const double *dbPolyPointsPositions,unsigned int intPointsCount,double dbContainerMinPosition,double dbContainerMaxPosition,double dbPositionType) {
    if (fabs(dbPositionType)<1) {
        return dbContainerMinPosition+dbPositionType*(dbContainerMaxPosition-dbContainerMinPosition);
    }
    else if (!isInRange(dbPositionType,ALIGN_NONE,-1,true,true)) {
        return getAlignedPolyContainerPosition(dbPolyPointsPositions,intPointsCount,dbContainerMinPosition,dbContainerMaxPosition,(enum ALIGNEMENTS) ROUND(dbPositionType));
    }
    else {
        return dbContainerMinPosition+dbPolyPointsPositions[getArrayMinItemIndex((const void *) dbPolyPointsPositions,intPointsCount,DOUBLE_MEMORY_ITEM)];
    }
}
