#include <stdlib.h>
#include "../../clibs/libfile/getFileDataSegment2.h"
#include "../../clibs/libmath/isInRange.h"
#include "getWadFileData.h"
//version finale
void *getWadFileData(FILE *fpwad,struct stWadMap *stWadFileMap,int intWadData,size_t *intDataSize,size_t intAlignedBufferBlockSize) {
void *varout=NULL;
    if (isInRange(intWadData,WAD_FOOTER_DATA,stWadFileMap->intTmdContentsCount,true,false)) {
        *intDataSize=0;
    }
    else {
        switch(intWadData) {
            case WAD_CERTS_DATA:
                *intDataSize=stWadFileMap->intCertsDataSize;
                varout=getFileDataSegment2(fpwad,stWadFileMap->intOffsetCertsData,*intDataSize,SEEK_SET,intAlignedBufferBlockSize);
                break;
            case WAD_CRL_DATA:
                *intDataSize=stWadFileMap->intCrlDataSize;
                varout=getFileDataSegment2(fpwad,stWadFileMap->intOffsetCrlData,*intDataSize,SEEK_SET,intAlignedBufferBlockSize);
                break;
            case WAD_TICKET_DATA:
                *intDataSize=stWadFileMap->intTicketDataSize;
                varout=getFileDataSegment2(fpwad,stWadFileMap->intOffsetTicketData,*intDataSize,SEEK_SET,intAlignedBufferBlockSize);
                break;
            case WAD_TMD_DATA:
                *intDataSize=stWadFileMap->intTmdDataSize;
                varout=getFileDataSegment2(fpwad,stWadFileMap->intOffsetTmdData,*intDataSize,SEEK_SET,intAlignedBufferBlockSize);
                break;
            case WAD_FOOTER_DATA:
                *intDataSize=stWadFileMap->intFooterDataSize;
                varout=getFileDataSegment2(fpwad,stWadFileMap->intOffsetFooterData,*intDataSize,SEEK_SET,intAlignedBufferBlockSize);
                break;
            default:
                *intDataSize=stWadFileMap->stTmdContents[intWadData].intContentDataSize;
                varout=getFileDataSegment2(fpwad,stWadFileMap->stTmdContents[intWadData].intOffsetContentData,*intDataSize,SEEK_SET,intAlignedBufferBlockSize);
        }
    }
    return varout;
}
