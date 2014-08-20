#include <ogc/cache.h>
#include <gctypes.h>
#include "../system/system.h"
#include "setGameSysramSettings.h"
#include "setGameSystemSettings.h"
void setGameSystemSettings(struct stGameConfig *stGamesSettings) {
    *TV_MODE=setGameSysramSettings(stGamesSettings);
	DCFlushRange((void *)TV_MODE,4);
}
