#include <string.h>
#include <gctypes.h>
#include <stdlib.h>
#include <malloc.h>
#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/macros.h"
#include "../titles/titles.h"
#include "../titles/getTitles.h"
#include "../titles/isIosTitleId.h"
#include "../titles/readStoredTmdDatas.h"
#include "getSlotsMap.h"
//version finale
extern unsigned short int intStubsMap[256];
struct stSlotInfos *getSlotsMap() {
static struct stStoredIosInfos {
    u16 intIosRevision __attribute__((aligned(0x20)));
    u8 chTmdContentHash[20] __attribute__((aligned(0x20)));
} stIosInfos;
struct stSlotInfos *varout=NULL;
u8 chIosCount;
u64 *intTitles=NULL;
u32 intTitlesCount,intMinorTitleId;
static enum TMD_DATAS TMD_DATAS_LIST[2]={TMD_TITLE_VERSION_DATA,GET_CONTENT_ENUM_TMD_DATA(0,TMD_CONTENT_HASH_DATA)};
static void *varAlignedTmdDatas[2]={&stIosInfos.intIosRevision,stIosInfos.chTmdContentHash};
    if ((intTitles=getTitles(&intTitlesCount))!=NULL) {
        if ((varout=calloc(256*SLOT_INFOS_STRUCTURE_SIZE,1))!=NULL) {
            chIosCount=0;
            while (chIosCount<intTitlesCount) {
                if (isIosTitleId(intTitles[chIosCount])) {
                    if (readStoredTmdDatas(intTitles[chIosCount],TMD_DATAS_LIST,varAlignedTmdDatas,2)) {
                        intMinorTitleId=MINOR_NUMBER(intTitles[chIosCount],u32);
                        memcpy(varout[intMinorTitleId].chTmdContentIdentificationHash,stIosInfos.chTmdContentHash,20);
                        if ((varout[intMinorTitleId].intIosRevision=stIosInfos.intIosRevision)==intStubsMap[intMinorTitleId]) {
                            varout[intMinorTitleId].chIosType=STUB_IOS;
                        }
                        else {
                            varout[intMinorTitleId].chIosType=ACTIVE_IOS;
                        }
                    }
                    else {
                        //TODO
                    }
                    chIosCount++;
                }
                else {
                    intTitlesCount--;
                    SWAP(&intTitles[chIosCount],&intTitles[intTitlesCount]);
                }
            }
            varout[FF4_IOS_MINOR_TID].chIosType=(varout[FF4_IOS_MINOR_TID].chIosType>STUB_IOS)?RESERVED_IOS:varout[FF4_IOS_MINOR_TID].chIosType;
            varout[BOOTMII_IOS_MINOR_TID].chIosType=(varout[BOOTMII_IOS_MINOR_TID].chIosType>STUB_IOS)?BOOTMII_IOS:varout[BOOTMII_IOS_MINOR_TID].chIosType;
        }
        freeVector((void **) &intTitles);
    }
    return varout;
}
