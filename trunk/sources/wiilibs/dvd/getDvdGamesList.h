#ifndef _GETDVDGAMESLIST_H_
#define _GETDVDGAMESLIST_H_
#include "../dvd/dvd.h"
#include "../filesystems/filesystems.h"
struct stDvdDiscInfos *getDvdGamesList(const char *strGamesPath,enum STORAGE_DEVICES STORAGE_DEVICE,enum DVD_DISC_TYPES DVD_DISC_TYPE,unsigned int *intGamesCount);
#endif
