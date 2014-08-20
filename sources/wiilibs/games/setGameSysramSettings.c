#include <ogc/system.h>
#include <ogc/video.h>
#include <ogc/conf.h>
#include "../system/getWiiSystemSramLanguage.h"
#include "../system/system.h"
#include "setGameSysramSettings.h"
syssram* __SYS_LockSram();
u32 __SYS_UnlockSram(u32 write);
u32 __SYS_SyncSram(void);
u32 setGameSysramSettings(struct stGameConfig *stGamesSettings) {
syssram *sram;
u32 varout=0;
    sram=__SYS_LockSram();
    if (((VIDEO_HaveComponentCable()) && (CONF_GetProgressiveScan()>0)) || (stGamesSettings->VIDEO_MODE>NTSC480I_VIDEO_MODE)) {
		sram->flags=sram->flags | 0x80;
    }
	else {
		sram->flags=sram->flags & 0x7F;
	}
	if ((stGamesSettings->VIDEO_MODE==PAL50_VIDEO_MODE) || (stGamesSettings->VIDEO_MODE==PAL60_VIDEO_MODE) || (stGamesSettings->VIDEO_MODE==PAL480P_VIDEO_MODE) || (stGamesSettings->VIDEO_MODE==PATCHED_PAL480P_VIDEO_MODE)) {
		if (stGamesSettings->VIDEO_MODE==PAL50_VIDEO_MODE) {
            varout=1;
		}
		else {
            varout=5;
		}
		sram->flags=sram->flags | 0x01;
		sram->ntd=sram->ntd | 0x40;
	}
	else {
		sram->flags=sram->flags & 0xFE;
		sram->ntd=sram->ntd & 0xBF;
	}
	sram->lang=(stGamesSettings->GAME_LANGUAGE==SRAM_GC_CONSOLE_LANGUAGE)?getWiiSystemSramLanguage():stGamesSettings->GAME_LANGUAGE;
	__SYS_UnlockSram(1);
    while(!__SYS_SyncSram());
    return varout;
}
