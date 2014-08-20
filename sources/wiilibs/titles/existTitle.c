#include <ogc/es.h>
#include "../nand/existNandTitle.h"
#include "../nand/haveNandAccess.h"
#include "existTitle.h"
//version finale
bool existTitle(u64 intTitleId) {
u32 intTmdSize;
    if (haveNandAccess()) {
        return existNandTitle(intTitleId);
    }
    else {
        return (ES_GetStoredTMDSize(intTitleId,&intTmdSize)>-1);
    }
}
