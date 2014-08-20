#include <stdlib.h>
#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/macros.h"
#include "../titles/installTmdContent.h"
#include "getWadFileData.h"
#include "installWadTmdContents.h"
//version finale
s32 installWadTmdContents(FILE *fpwad,struct stWadMap *stWadFileMap,const signed_blob *sTmd,u32 intTmdSize,const signed_blob *sCerts,u32 intCertsSize,const signed_blob *sCrl,u32 intCrlsize) {
s32 varout;
tmd *pTmd;
u8 *chContentBuffer=NULL;
    if ((varout=ES_AddTitleStart(sTmd,intTmdSize,sCerts,intCertsSize,sCrl,intCrlsize))<0) {
        goto CANCELTITLE;
    }
    else {
        pTmd=SIGNATURE_PAYLOAD(sTmd);
        for (intCrlsize=0;intCrlsize<pTmd->num_contents;intCrlsize++) {
            if ((chContentBuffer=getWadFileData(fpwad,stWadFileMap,intCrlsize,&intTmdSize,32))==NULL) {
                goto CANCELTITLE;
            }
            else {
                if ((varout=installTmdContent(pTmd->title_id,pTmd->contents[intCrlsize].cid,chContentBuffer,intTmdSize))<0) {
                    freeVector((void **) &chContentBuffer);
                    goto CANCELTITLE;
                }
                freeVector((void **) &chContentBuffer);
            }
        }
        if ((varout=ES_AddTitleFinish())<0) {
            goto CANCELTITLE;
        }
    }
    EXITFUNCTION:
    return varout;
    CANCELTITLE:
    ES_AddTitleCancel();
    varout=MIN(varout,-1);
    goto EXITFUNCTION;
}
