#ifndef _DOL_H_
#define _DOL_H_
#include <stddef.h>
#include <gctypes.h>
#include "../../clibs/libtools/libtools.h"
#define DOL_ENTRY_POINT_OFFSET 0xe0
#define DOL_ADDRESS_LIMIT 0x80700000
#define DOL_IMAGE_LOWER_ENTRY_POINT (void *) 0x80100000
#define DOL_IMAGE_ENTRY_POINT (void *) 0x80A00000
#define GC_DOL_IMAGE_MAXSIZE 0x00800000
struct stDolInfo {
    struct stBytesPattern stSearchPattern;
    size_t intInfoSize;
};
struct stDolInfos {
    char *strName;
    struct stDolInfo *stInfos;
    unsigned char chInfosCount;
    unsigned char chMagicBytesPattern;
};
struct stDolHeader {
    u32 intTextsOffsets[7];
    u32 intDatasOffsets[11];
    u32 intTextsLoadingAddresses[7];
    u32 intDatasLoadingAddresses[11];
    u32 intTextsSizes[7];
    u32 intDatasSizes[11];
    u32 intBssOffset;
    u32 intBssSize;
    u32 intEntryPoint;
    u8 chPadding[28];
};
enum {
    DOL_INFO_STRUCTURE_SIZE=sizeof(struct stDolInfo),
    DOL_INFOS_STRUCTURE_SIZE=sizeof(struct stDolInfos),
    DOL_HEADER_STRUCTURE_SIZE=sizeof(struct stDolHeader)
};
#endif
