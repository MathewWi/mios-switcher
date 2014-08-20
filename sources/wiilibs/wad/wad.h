#ifndef _WAD_H_
#define _WAD_H_
#define WADS_FOLDER_PATH "/wad"
#if defined(_WIN64) || defined(_WIN32)
#include "../../clibs/ctypes.h"
#else
#include <gctypes.h>
#endif
#include <stddef.h>
struct stWadHeader {
	u32 intHeaderSize;
	u16 intWadType;
    u16 intPadding;
    u32 intCertsSize;
	u32 intCrlSize;
	u32 intTicketSize;
	u32 intTmdSize;
	u32 intDataSize;
	u32 intFooterSize;
} __attribute__((packed));
struct stWadContent {
    unsigned int intOffsetContentData;
    size_t intContentDataSize;
};
struct stWadMap {
    unsigned int intOffsetCertsData;
    size_t intCertsDataSize;
    unsigned int intOffsetCrlData;
    size_t intCrlDataSize;
    unsigned int intOffsetTicketData;
    size_t intTicketDataSize;
    unsigned int intOffsetTmdData;
    size_t intTmdDataSize;
    u16 intTmdContentsCount;
    struct stWadContent *stTmdContents;
    unsigned int intOffsetFooterData;
    size_t intFooterDataSize;
};
enum {
    WAD_HEADER_STRUCTURE_SIZE=sizeof(struct stWadHeader),
	WAD_CONTENT_STRUCTURE_SIZE=sizeof(struct stWadContent)
};
enum WAD_DATAS {
    WAD_CERTS_DATA=-1,
    WAD_CRL_DATA=-2,
    WAD_TICKET_DATA=-3,
    WAD_TMD_DATA=-4,
    WAD_FOOTER_DATA=-5
};
#endif
