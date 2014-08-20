#include "../../clibs/macros.h"
#include "readStoredTmdDatas.h"
#include "isIosTitleId.h"
#include "titles.h"
#include "isCriticalTitle.h"
extern unsigned short int intStubsMap[256];
bool isCriticalTitle(u64 intTitleId) {
static struct stStoredTitleInfos {
    u64 intSysVersion __attribute__((aligned(0x20)));
    u16 intTitleVersion __attribute__((aligned(0x20)));
} stStoredTitleTmdDatas;
static enum TMD_DATAS TMD_DATAS_LIST[2]={TMD_TITLE_VERSION_DATA,TMD_SYS_VERSION_DATA};
static void *varAlignedTmdDatas[2]={&stStoredTitleTmdDatas.intTitleVersion,&stStoredTitleTmdDatas.intSysVersion};
    switch (intTitleId) {
        case BOOT2_TID:
        case SYSTEM_MENU_TID:
        case FF4_IOS_TID:
        case BC_TID:
        case MIOS_TID:
            return true;
        case BOOTMII_IOS_TID:
            if (readStoredTmdDatas(BOOTMII_IOS_TID,TMD_DATAS_LIST,varAlignedTmdDatas,1)) {
                return (stStoredTitleTmdDatas.intTitleVersion!=intStubsMap[BOOTMII_IOS_MINOR_TID]);
            }
            break;
        default:
            if (isIosTitleId(intTitleId)) {
                if (readStoredTmdDatas(SYSTEM_MENU_TID,TMD_DATAS_LIST,varAlignedTmdDatas,2)==sizeof(stStoredTitleTmdDatas.intTitleVersion)+sizeof(stStoredTitleTmdDatas.intSysVersion)) {
                    if (stStoredTitleTmdDatas.intSysVersion==intTitleId) {
                        return (stStoredTitleTmdDatas.intTitleVersion!=intStubsMap[MINOR_NUMBER(intTitleId,u32)]);
                    }
                }
            }
    }
    return false;
}
