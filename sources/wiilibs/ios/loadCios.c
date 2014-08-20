#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ogc/ios.h>
#include "../../clibs/libmemory/freeVector.h"
#include "../titles/getXmlTitlesInfos.h"
#include "../titles/freeTitlesInfos.h"
#include "../titles/titles.h"
#include "CIOSINFOS_xml.h"
#include "ios.h"
#include "setAhbProtAccessRights.h"
#include "applyAhbProtPatchs.h"
#include "getSlotsMap.h"
#include "loadCios.h"
//version finale
void loadCios(bool blnTryAhbProt,u8 chDefaultCios) {
struct stSlotInfos *stSlotsMap=NULL;
struct stTitleInfos *stCiosInfos=NULL;
unsigned int intSupportedCiosCount,i;
    blnTryAhbProt=((blnTryAhbProt) && (setAhbProtAccessRights()>0));
    if (blnTryAhbProt) {
        blnTryAhbProt=(applyAhbProtPatchs()>0);
    }
    if (!blnTryAhbProt) {
        if ((stSlotsMap=getSlotsMap())!=NULL) {
            if (stSlotsMap[chDefaultCios].chIosType<ACTIVE_IOS) {
                if ((stCiosInfos=getXmlTitlesInfos((const char *) CIOSINFOS_xml,&intSupportedCiosCount))!=NULL) {
                    chDefaultCios=200;
                    while (chDefaultCios>199) {
                        if (stSlotsMap[chDefaultCios].chIosType>RESERVED_IOS) {
                            for (i=0;i<intSupportedCiosCount;i++) {
                                if (!memcmp(stSlotsMap[chDefaultCios].chTmdContentIdentificationHash,stCiosInfos[i].stIdentificationModule.chModuleHash,20)) {
                                    if ((strstr(stCiosInfos[i].strTitleLabel,"(38)")!=NULL) || (strstr(stCiosInfos[i].strTitleLabel,"(36)")!=NULL)) {
                                        goto EXITWHILE;
                                    }
                                }
                            }
                        }
                        chDefaultCios++;
                    }
                    EXITWHILE:
                    freeTitlesInfos(&stCiosInfos,intSupportedCiosCount);
                }
                while (stSlotsMap[chDefaultCios].chIosType<ACTIVE_IOS) {
                    chDefaultCios++;
                }
            }
            if (chDefaultCios!=IOS_GetVersion()) {
                IOS_ReloadIOS(chDefaultCios);
                sleep(1);
            }
            freeVector((void **) &stSlotsMap);
        }
    }
}
