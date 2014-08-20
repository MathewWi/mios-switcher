#include <stdlib.h>
#include <ogc/es.h>
#include "../../clibs/libmemory/freeVector.h"
#include "getWadFileData.h"
#include "installWadTmdContents.h"
#include "installWadFile2.h"
//version finale
s32 installWadFile2(FILE *fpwad,struct stWadMap *stWadFileMap) {
s32 varout=-1;
signed_blob *chCertsBuffer=NULL,*chCrlBuffer=NULL,*chTicketBuffer=NULL,*chTmdBuffer=NULL;
    if ((chCertsBuffer=getWadFileData(fpwad,stWadFileMap,WAD_CERTS_DATA,&stWadFileMap->intCertsDataSize,32))!=NULL) {
        chCrlBuffer=getWadFileData(fpwad,stWadFileMap,WAD_CRL_DATA,&stWadFileMap->intCrlDataSize,32);
        if ((chTicketBuffer=getWadFileData(fpwad,stWadFileMap,WAD_TICKET_DATA,&stWadFileMap->intTicketDataSize,32))!=NULL) {
            if ((chTmdBuffer=getWadFileData(fpwad,stWadFileMap,WAD_TMD_DATA,&stWadFileMap->intTmdDataSize,32))!=NULL) {
                if ((varout=ES_AddTicket(chTicketBuffer,stWadFileMap->intTicketDataSize,chCertsBuffer,stWadFileMap->intCertsDataSize,chCrlBuffer,stWadFileMap->intCrlDataSize))>-1) {
                    if ((varout=installWadTmdContents(fpwad,stWadFileMap,chTmdBuffer,stWadFileMap->intTmdDataSize,chCertsBuffer,stWadFileMap->intCertsDataSize,chCrlBuffer,stWadFileMap->intCrlDataSize))>-1) {
                        //TODO
                    }
                }
                freeVector((void **) &chTmdBuffer);
            }
            freeVector((void **) &chTicketBuffer);
        }
        freeVector((void **) &chCrlBuffer);
        freeVector((void **) &chCertsBuffer);
    }
    return varout;
}
