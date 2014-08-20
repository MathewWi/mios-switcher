#include <string.h>
#include <stdlib.h>
#include <ogc/dvd.h>
#include "../filesystems/filesystems.h"
#include "initGameDvd.h"
#include "getDvdGameTitle.h"
#include "getDvdGameDiscInfos.h"
struct stDvdDiscInfos *getDvdGameDiscInfos() {
static struct stDvdDiscInfos varout={{0,0,0,0,0,0},0,0,0,0,UNKNOWN_DVD_DISC,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},RAW_GAME_FORMAT,DVD_STORAGE_DEVICE};
dvddiskid *stDvdDiskId;
    if ((stDvdDiskId=initGameDvd())!=NULL) {
        if ((*(u32 *)((void *) stDvdDiskId+GC_MAGICWORD_OFFSET)==GC_MAGICWORD)) {
            varout.DVD_DISC_TYPE=GC_DVD_DISC;
        }
        else if (*(u32 *)((void *) stDvdDiskId+WII_MAGICWORD_OFFSET)==WII_MAGICWORD) {
            varout.DVD_DISC_TYPE=WII_DVD_DISC;
        }
        else {
            return NULL;
        }
        memcpy(varout.strDiscID,stDvdDiskId,10);
        if ((stDvdDiskId=(dvddiskid *) getDvdGameTitle())!=NULL) {
            memcpy(varout.strGameTitle,stDvdDiskId,64);
            return &varout;
        }
    }
    return NULL;
}
