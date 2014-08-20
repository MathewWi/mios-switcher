#ifndef _GETGAMESSETTINGS_H_
#define _GETGAMESSETTINGS_H_
#include "../dvd/dvd.h"
#include "games.h"
struct stGameConfig **getGamesSettings(struct stDvdDiscInfos *stGamesInfos,unsigned int intGamesCount,struct stGameConfig **stGamesIniSettings,unsigned int *intIniSettingsCount,struct stGameConfig *stDefaultGameConfig);
#endif
