#ifndef _GAMES_H_
#define _GAMES_H_
#include <stdbool.h>
#include <ogc/gx_struct.h>
#include "../titles/titles.h"
#include "../mios/mios.h"
#include "../video/video.h"
#include "../system/system.h"
struct stGameConfig {
    char strDiscID[7];
    struct stDiosMiosSettings stDiosMiosConfig;
    struct stTitleIdentificationModule stIosIdentificationModule;
    enum VIDEO_MODES VIDEO_MODE;
    enum SRAM_GC_LANGUAGES GAME_LANGUAGE;
    bool blnDriveReset;
    bool blnNtscjPatch;
};
enum {
    GAME_CONFIG_STRUCTURE_SIZE=sizeof(struct stGameConfig)
};
#endif
