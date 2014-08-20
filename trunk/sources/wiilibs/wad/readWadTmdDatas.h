#ifndef _READWADTMDDATAS_H_
#define _READWADTMDDATAS_H_
#include <stddef.h>
#include <stdio.h>
#include "../titles/titles.h"
#include "wad.h"
size_t readWadTmdDatas(FILE *fpwad,struct stWadMap *stWadFileMap,enum TMD_DATAS *TMD_DATAS_LIST,void **varTmdDatas,unsigned char chTmdDatasCount);
#endif
