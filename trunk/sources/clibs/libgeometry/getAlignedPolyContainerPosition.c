#include "../libmemory/libmemory.h"
#include "../libarray/getArrayMaxItemIndex.h"
#include "../libarray/getArrayMinItemIndex.h"
#include "getAlignedPolyContainerPosition.h"
//version finale
double getAlignedPolyContainerPosition(const double *dbPolyPointsPositions,unsigned int intPointsCount,double dbContainerMinPosition,double dbContainerMaxPosition,enum ALIGNEMENTS ALIGNEMENT) {
	switch(ALIGNEMENT) {
		case ALIGN_LEFT:
			return dbContainerMinPosition;
			break;
		case ALIGN_CENTER:
            return dbContainerMinPosition+(dbContainerMaxPosition-dbContainerMinPosition-dbPolyPointsPositions[getArrayMaxItemIndex((const void *) dbPolyPointsPositions,intPointsCount,DOUBLE_MEMORY_ITEM)]+dbPolyPointsPositions[getArrayMinItemIndex((const void *) dbPolyPointsPositions,intPointsCount,DOUBLE_MEMORY_ITEM)])/2;
			break;
		case ALIGN_RIGHT:
			return dbContainerMaxPosition-dbPolyPointsPositions[getArrayMaxItemIndex((const void *) dbPolyPointsPositions,intPointsCount,DOUBLE_MEMORY_ITEM)]+dbPolyPointsPositions[getArrayMinItemIndex((const void *) dbPolyPointsPositions,intPointsCount,DOUBLE_MEMORY_ITEM)];
			break;
        default:
            return dbContainerMinPosition+dbPolyPointsPositions[getArrayMinItemIndex((const void *) dbPolyPointsPositions,intPointsCount,DOUBLE_MEMORY_ITEM)];
            break;
	};
}
