#if defined(_WIN64) || defined(_WIN32)
#include "../../clibs/libtools/swapBytes.h"
#endif
#include "../../clibs/macros.h"
#include "isWad.h"
#include "setWadFileMapHeader.h"
//version finale
bool setWadFileMapHeader(struct stWadHeader *stWadTitleHeader,struct stWadMap *stWadFileMap) {
bool varout;
    if ((varout=isWad(stWadTitleHeader))) {
        stWadFileMap->intOffsetCertsData=stWadTitleHeader->intHeaderSize;
        stWadFileMap->intCertsDataSize=stWadTitleHeader->intCertsSize;
        stWadFileMap->intCrlDataSize=stWadTitleHeader->intCrlSize;
        stWadFileMap->intTicketDataSize=stWadTitleHeader->intTicketSize;
        stWadFileMap->intTmdDataSize=stWadTitleHeader->intTmdSize;
#if defined(_WIN64) || defined(_WIN32)
        swapBytes((unsigned char *) &stWadFileMap->intOffsetCertsData,sizeof(stWadFileMap->intOffsetCertsData));
        swapBytes((unsigned char *) &stWadFileMap->intCertsDataSize,sizeof(stWadFileMap->intCertsDataSize));
        swapBytes((unsigned char *) &stWadFileMap->intCrlDataSize,sizeof(stWadFileMap->intCrlDataSize));
        swapBytes((unsigned char *) &stWadFileMap->intTicketDataSize,sizeof(stWadFileMap->intTicketDataSize));
        swapBytes((unsigned char *) &stWadFileMap->intTmdDataSize,sizeof(stWadFileMap->intTmdDataSize));
#endif
        stWadFileMap->intOffsetCertsData=ROUND_UP(stWadFileMap->intOffsetCertsData,64);
        stWadFileMap->intOffsetCrlData=stWadFileMap->intOffsetCertsData+ROUND_UP(stWadFileMap->intCertsDataSize,64);
        stWadFileMap->intOffsetTicketData=stWadFileMap->intOffsetCrlData+ROUND_UP(stWadFileMap->intCrlDataSize,64);
        stWadFileMap->intOffsetTmdData=stWadFileMap->intOffsetTicketData+ROUND_UP(stWadFileMap->intTicketDataSize,64);
    }
    return varout;
}
