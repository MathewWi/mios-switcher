#include <stdlib.h>
#if defined(_WIN64) || defined(_WIN32)
#include "../../clibs/libwii/libwii.h"
#else
#include <ogc/es.h>
#endif
#include "../../clibs/libfile/getFileDataSegment2.h"
#include "../../clibs/libmemory/freeVector.h"
#include "setWadFileMapHeader.h"
#include "setWadFileMapFooter.h"
#include "setWadFileMap.h"
//version finale
bool setWadFileMap(FILE *fpwad,struct stWadMap *stWadFileMap) {
bool varout=false;
struct stWadHeader *stWadTitleHeader=NULL;
signed_blob *sTmd=NULL,*sCerts=NULL,*sTicket=NULL;
    if ((stWadTitleHeader=getFileDataSegment2(fpwad,0,WAD_HEADER_STRUCTURE_SIZE,SEEK_SET,0))!=NULL) {
        if (setWadFileMapHeader(stWadTitleHeader,stWadFileMap)) {
            if ((sCerts=getFileDataSegment2(fpwad,stWadFileMap->intOffsetCertsData,stWadFileMap->intCertsDataSize,SEEK_SET,0))!=NULL) {
                if (IS_VALID_SIGNATURE(sCerts)) {
                    if ((sTicket=getFileDataSegment2(fpwad,stWadFileMap->intOffsetTicketData,stWadFileMap->intTicketDataSize,SEEK_SET,0))!=NULL) {
                        if (IS_VALID_SIGNATURE(sTicket)) {
                            if ((sTmd=getFileDataSegment2(fpwad,stWadFileMap->intOffsetTmdData,stWadFileMap->intTmdDataSize,SEEK_SET,0))!=NULL) {
                                varout=setWadFileMapFooter(sTmd,stWadTitleHeader,stWadFileMap);
                                freeVector((void **) &sTmd);
                            }
                        }
                        freeVector((void **) &sTicket);
                    }
                }
                freeVector((void **) &sCerts);
            }
        }
        freeVector((void **) &stWadTitleHeader);
    }
    return varout;
}
