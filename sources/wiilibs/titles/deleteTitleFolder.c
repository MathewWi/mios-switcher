#include <ogc/es.h>
#include "../nand/haveNandAccess.h"
#include "../nand/deleteNandTitleFolder.h"
#include "deleteTitleFolder.h"
s32 deleteTitleFolder(u64 intTitleId) {
s32 varout;
    if (haveNandAccess()) {
        varout=deleteNandTitleFolder(intTitleId);
    }
	else {
	    if ((varout=ES_DeleteTitleContent(intTitleId))<0) {
            //TODO
	    }
	    else {
            if ((varout=ES_DeleteTitle(intTitleId))<0) {
                //TODO
            }
	    }
    }
	return varout;
}
