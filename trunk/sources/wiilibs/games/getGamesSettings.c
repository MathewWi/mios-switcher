#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../clibs/libarray/getArrayMemoryItemIndex.h"
#include "../../clibs/libmemory/expandVector.h"
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "../../clibs/clibs.h"
#include "../video/video.h"
#include "setGameVideoSettings.h"
#include "getGamesSettings.h"
struct stGameConfig **getGamesSettings(struct stDvdDiscInfos *stGamesInfos,unsigned int intGamesCount,struct stGameConfig **stGamesIniSettings,unsigned int *intIniSettingsCount,struct stGameConfig *stDefaultGameConfig) {
struct stGameConfig **varout=NULL;
    if (expandVector((void **) stGamesIniSettings,*intIniSettingsCount,intGamesCount,stDefaultGameConfig,GAME_CONFIG_STRUCTURE_SIZE)!=NULL) {
        if ((varout=getDynamicMemory(intGamesCount*POINTER_TYPE_SIZE))!=NULL) {
            while (intGamesCount) {
                intGamesCount--;
                varout[intGamesCount]=((void *) *stGamesIniSettings+getArrayMemoryItemIndex((*stGamesIniSettings)[0].strDiscID,*intIniSettingsCount,stGamesInfos[intGamesCount].strDiscID,6,GAME_CONFIG_STRUCTURE_SIZE,false)*GAME_CONFIG_STRUCTURE_SIZE);
                if (!varout[intGamesCount]->strDiscID[0]) {
                    strncpy(varout[intGamesCount]->strDiscID,stGamesInfos[intGamesCount].strDiscID,6);
                    snprintf(varout[intGamesCount]->stDiosMiosConfig.strGamePath,sizeof(varout[intGamesCount]->stDiosMiosConfig.strGamePath),"%s/%s/game.iso",GC_DVD_BACKUP_GAMES_PATH,varout[intGamesCount]->strDiscID);
                    setGameVideoSettings(varout[intGamesCount],AUTO_VIDEO_MODE);
                    *intIniSettingsCount=*intIniSettingsCount+1;
                }
            }
        }
    }
    return varout;
}
