#include <malloc.h>
#include <gctypes.h>
#include <stdlib.h>
#include "../../clibs/libmemory/reallocBuffer.h"
#include "../../clibs/libarray/getArrayMemoryItemIndex.h"
#include "../../clibs/clibs.h"
#include "../titles/existTitle.h"
#include "../titles/readStoredTmdDatas.h"
#include "getInstalledMiosInfos.h"
//version finale
struct stTitleInfos **getInstalledMiosInfos(unsigned char *chInstalledMiosCount,struct stTitleInfos *stKnownMiosInfos,unsigned int intKnownMiosCount) {
struct stTitleInfos **varout=NULL;
static struct stStoredMiosInfos {
    u64 intTitleId __attribute__((aligned(0x20)));
    u8 chBootContentHash[20] __attribute__((aligned(0x20)));
} stInstalledMiosInfos;
static enum TMD_DATAS TMD_DATAS_LIST[2]={TMD_TITLE_ID_DATA,GET_CONTENT_ENUM_TMD_DATA(1,TMD_CONTENT_HASH_DATA)};
static void *varAlignedTmdDatas[2]={&stInstalledMiosInfos.intTitleId,stInstalledMiosInfos.chBootContentHash};
    *chInstalledMiosCount=0;
    if ((varout=malloc(256*POINTER_TYPE_SIZE))!=NULL) {
        stInstalledMiosInfos.intTitleId=0;
        while ((existTitle(*chInstalledMiosCount+MIOS_TID)) && (stInstalledMiosInfos.intTitleId<intKnownMiosCount)) {
            if (readStoredTmdDatas(*chInstalledMiosCount+MIOS_TID,TMD_DATAS_LIST,varAlignedTmdDatas,2)==sizeof(stInstalledMiosInfos.intTitleId)+sizeof(stInstalledMiosInfos.chBootContentHash)) {
                if (stInstalledMiosInfos.intTitleId==MIOS_TID) {
                    if ((stInstalledMiosInfos.intTitleId=getArrayMemoryItemIndex(stKnownMiosInfos[0].stIdentificationModule.chModuleHash,intKnownMiosCount,stInstalledMiosInfos.chBootContentHash,20,TITLE_INFOS_STRUCTURE_SIZE,false))<intKnownMiosCount) {
                        varout[*chInstalledMiosCount]=&stKnownMiosInfos[stInstalledMiosInfos.intTitleId];
                        *chInstalledMiosCount=*chInstalledMiosCount+1;
                    }
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        reallocBuffer((void **) &varout,*chInstalledMiosCount*POINTER_TYPE_SIZE,0);
    }
    return varout;
}
