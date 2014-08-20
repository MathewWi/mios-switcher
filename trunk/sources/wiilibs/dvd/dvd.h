#ifndef _DVD_H_
#define _DVD_H_
#include <string.h>
#include <gctypes.h>
#include <ogc/dvd.h>
#include <di/di.h>
#include "../filesystems/filesystems.h"
#define GAME_TITLE_OFFSET 0x020
#define GC_MAGICWORD_OFFSET 0x1c
#define GC_MAGICWORD 0xc2339f3d
#define WII_MAGICWORD_OFFSET 0x18
#define WII_MAGICWORD 0x5d1c9ea3
#define IS_BACKUP_RESISTANT_DVD_DRIVE(d) (d.rel_date>0x20070213)
#define WII_DVD_BACKUP_GAMES_PATH "/wbfs"
#define GC_DVD_BACKUP_GAMES_PATH "/games"
#define IOCTL_DI_DVDLowAudioBufferConfig 0xE4
enum DVD_GAME_FORMATS {
    RAW_GAME_FORMAT=0,
    FST_GAME_FORMAT=1,
    ISO_GAME_FORMAT=2,
    WBFS_GAME_FORMAT=3,
};
enum DVD_DISC_TYPES {
    UNKNOWN_DVD_DISC=0,
    GC_DVD_DISC=1,
    WII_DVD_DISC=2,
    ALL_DVD_DISCS=GC_DVD_DISC | WII_DVD_DISC
};
enum DVD_READ_MODES {
    DVD_LOW_READ_MODE=DVD_LOW_READ,
    DVD_UNENCRYPTED_READ_MODE=DVD_READ_UNENCRYPTED
};
struct stDvdDiscInfos {
    char strDiscID[6];
    u8 intDiscNumber;
    u8 intDiscVersion;
    u8 intAudioStreaming;
    u8 intStreamingBufferSize;
    enum DVD_DISC_TYPES DVD_DISC_TYPE;
    char strGameTitle[64];
    enum DVD_GAME_FORMATS DVD_GAME_FORMAT;
    enum STORAGE_DEVICES STORAGE_DEVICE;
};
enum {
    GC_DVD_BACKUP_GAMES_PATH_MAXLENGTH=strlen(GC_DVD_BACKUP_GAMES_PATH)+1+STORAGE_DEVICE_NAME_MAXLENGTH,
    DVD_DISC_INFOS_STRUCTURE_SIZE=sizeof(struct stDvdDiscInfos)
};
#endif
