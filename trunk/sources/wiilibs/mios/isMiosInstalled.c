#include <string.h>
#include "isMiosInstalled.h"
//version finale
bool isMiosInstalled(u8 *chMiosBootContentHash,struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount) {
    while (chInstalledMiosCount) {
        chInstalledMiosCount--;
        if (!memcmp(chMiosBootContentHash,stInstalledMiosInfos[chInstalledMiosCount]->stIdentificationModule.chModuleHash,20)) {
            return true;
        }
    }
    return false;
}
