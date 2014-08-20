#include "deleteTitleTicket.h"
#include "deleteTitleFolder.h"
#include "isCriticalTitle.h"
#include "uninstallTitle.h"
s32 uninstallTitle(u64 intTitleId,bool blnSafeMode) {
s32 varout;
	if ((blnSafeMode=(blnSafeMode)?!isCriticalTitle(intTitleId):true)) {
	    if ((varout=deleteTitleTicket(intTitleId))<0) {
            //TODO
	    }
	    else {
            if ((varout=deleteTitleFolder(intTitleId))<0) {
                //TODO
            }
	    }
	}
	else {
        varout=-1;
	}
	return varout;
}
