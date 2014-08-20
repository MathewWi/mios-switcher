#ifndef _READDVDGAMEINFOS_H_
#define _READDVDGAMEINFOS_H_
#include <stdio.h>
#include "dvd.h"
enum DVD_DISC_TYPES readDvdGameInfos(FILE *fhDisc,unsigned int intHeaderOffset,struct stDvdDiscInfos *stDiscInfos);
#endif
