#include "../../clibs/libmemory/freeMemoryItemsVectors.h"
#include "../../clibs/libmemory/freeVector.h"
#include "freeTitlesInfos.h"
//version finale
void freeTitlesInfos(struct stTitleInfos **stTitlesInfos,unsigned int intTitlesCount) {
    freeMemoryItemsVectors(intTitlesCount,TITLE_INFOS_STRUCTURE_SIZE,2,(void **) &stTitlesInfos[0]->strTitleLabel,(void **) &stTitlesInfos[0]->strTitleInfos);
    freeVector((void **) stTitlesInfos);
}
