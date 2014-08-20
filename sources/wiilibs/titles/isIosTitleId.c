#include "../../clibs/libmath/isInRange.h"
#include "titles.h"
#include "isIosTitleId.h"
//version finale
bool isIosTitleId(u64 intTitleId) {
    return (!isInRange(intTitleId,SYSTEM_MENU_TID,BC_TID,false,false));
}
