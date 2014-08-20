#include <stddef.h>
#include <stdlib.h>
#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/libfile/getFileContent.h"
#include "getGamesIniSettings.h"
struct stGameConfig *getGamesIniSettings(const char *strIniFilename,unsigned int *intGamesSettingsCount) {
struct stGameConfig *varout=NULL;
    if ((varout=getFileContent(strIniFilename,intGamesSettingsCount,0))!=NULL) {
        if ((*intGamesSettingsCount % GAME_CONFIG_STRUCTURE_SIZE)) {
            freeVector((void **) &varout);
            *intGamesSettingsCount=0;
        }
        else {
            *intGamesSettingsCount=*intGamesSettingsCount/GAME_CONFIG_STRUCTURE_SIZE;
        }
    }
    return varout;
}
