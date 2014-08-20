#include <stdlib.h>
#include <ogc/es.h>
#include "../../clibs/libmemory/getAlignedBuffer.h"
#include "../../clibs/libmemory/freeVector.h"
#include "../nand/haveNandAccess.h"
#include "../nand/deleteNandTitleTicket.h"
#include "titles.h"
#include "deleteTitleTicket.h"
s32 deleteTitleTicket(u64 intTitleId) {
s32 varout;
tikview *pTikViews=NULL;
u32 intTikViewsCount;
    if (haveNandAccess()) {
        varout=deleteNandTitleTicket(intTitleId);
    }
	else {
        if ((varout=ES_GetNumTicketViews(intTitleId,&intTikViewsCount))<0) {
            //TODO
        }
        else {
            if ((pTikViews=getAlignedBuffer(TIKVIEW_STRUCTURE_SIZE*intTikViewsCount,32))==NULL) {
                varout=-1;
            }
            else {
                if ((varout=ES_GetTicketViews(intTitleId,pTikViews,intTikViewsCount))<0) {
                    //TODO
                }
                else {
                    while ((intTikViewsCount) && (varout>-1)) {
                        intTikViewsCount--;
                        varout=ES_DeleteTicket(&pTikViews[intTikViewsCount]);
                    }
                }
                freeVector((void **) &pTikViews);
            }
        }
	}
	return varout;
}
