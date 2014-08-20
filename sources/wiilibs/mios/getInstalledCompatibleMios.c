#include <string.h>
#include <stdlib.h>
#include "../../clibs/libtools/checkMetadataValue.h"
#include "../../clibs/libtools/libtools.h"
#include "../../clibs/clibs.h"
#include "../filesystems/getDeviceLabel.h"
#include "mios.h"
#include "getInstalledCompatibleMios.h"
struct stTitleInfos ***getInstalledCompatibleMios(const char *strDiscID,enum STORAGE_DEVICES STORAGE_DEVICE,struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount,unsigned char *chInstalledCompatibleMiosCount) {
static struct stTitleInfos **varout[256];
enum METADATA_CHECKING_STATUS intMetadataCheckingStatus;
    *chInstalledCompatibleMiosCount=0;
    while (chInstalledMiosCount) {
        chInstalledMiosCount--;
        if (checkMetadataValue(stInstalledMiosInfos[chInstalledMiosCount]->strTitleInfos,'|','=',',',MIOS_INFOS_DEVICES_LABEL,getDeviceLabel(STORAGE_DEVICE))==MATCHING_METADATA_STATUS) {
            if ((intMetadataCheckingStatus=checkMetadataValue(stInstalledMiosInfos[chInstalledMiosCount]->strTitleInfos,'|','=',',',MIOS_INFOS_DEDICATED_TITLES_LABEL,strDiscID))==MATCHING_METADATA_STATUS) {
                varout[0]=&stInstalledMiosInfos[chInstalledMiosCount];
                *chInstalledCompatibleMiosCount=1;
                break;
            }
            else {
                if (intMetadataCheckingStatus==MISSING_METADATA_STATUS) {
                    if (checkMetadataValue(stInstalledMiosInfos[chInstalledMiosCount]->strTitleInfos,'|','=',',',MIOS_INFOS_UNSUPPORTED_TITLES_LABEL,strDiscID)!=MATCHING_METADATA_STATUS) {
                        if (checkMetadataValue(stInstalledMiosInfos[chInstalledMiosCount]->strTitleInfos,'|','=',',',MIOS_INFOS_PRIORITY_TITLES_LABEL,strDiscID)==MATCHING_METADATA_STATUS) {
                            memmove(&varout[1],&varout[0],*chInstalledCompatibleMiosCount*POINTER_TYPE_SIZE);
                            varout[0]=&stInstalledMiosInfos[chInstalledMiosCount];
                        }
                        else {
                            varout[*chInstalledCompatibleMiosCount]=&stInstalledMiosInfos[chInstalledMiosCount];
                        }
                        *chInstalledCompatibleMiosCount=*chInstalledCompatibleMiosCount+1;
                    }
                }
            }
        }
    }
    return (*chInstalledCompatibleMiosCount)?varout:NULL;
}
