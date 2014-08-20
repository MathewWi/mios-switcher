#include "existTitle.h"
#include "getNextFreeTitleId.h"
//version finale
u64 getNextFreeTitleId(u64 intStartTitleId) {
    while (existTitle(intStartTitleId)) {
        intStartTitleId++;
    }
    return intStartTitleId;
}
