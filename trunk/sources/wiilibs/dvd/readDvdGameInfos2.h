#ifndef _READDVDGAMEINFOS2_H_
#define _READDVDGAMEINFOS2_H_
#include <stdio.h>
#include <stdbool.h>
#include "dvd.h"
bool readDvdGameInfos2(FILE *fhDisc,unsigned int intHeaderOffset,struct stDvdDiscInfos *stDiscInfos);
#endif
