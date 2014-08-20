#ifndef _READSTOREDTMDDATAS_H_
#define _READSTOREDTMDDATAS_H_
#include <stddef.h>
#include <gctypes.h>
#include "titles.h"
size_t readStoredTmdDatas(u64 intTitleId,enum TMD_DATAS *TMD_DATAS_LIST,void **varAlignedTmdDatas,unsigned char chTmdDatasCount);
#endif
