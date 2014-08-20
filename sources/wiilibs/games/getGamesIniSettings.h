#ifndef _GETGAMESINISETTINGS_H_
#define _GETGAMESINISETTINGS_H_
#include "games.h"
struct stGameConfig *getGamesIniSettings(const char *strIniFilename,unsigned int *intGamesSettingsCount);
#endif
