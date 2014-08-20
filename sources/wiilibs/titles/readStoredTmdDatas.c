#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ogc/es.h>
#include <ogc/isfs.h>
#include "../../clibs/macros.h"
#include "../../clibs/libmemory/freeVector.h"
#include "../nand/readNandFileDataSegment.h"
#include "getStoredTmd.h"
#include "readStoredTmdDatas.h"
//version finale
size_t readStoredTmdDatas(u64 intTitleId,enum TMD_DATAS *TMD_DATAS_LIST,void **varAlignedTmdDatas,unsigned char chTmdDatasCount) {
size_t varout=0;
signed_blob *sTmd=NULL;
u32 intAlignedBuffer __attribute__((aligned(0x20)));
u16 intTmdContentsCount __attribute__((aligned(0x20)));
tmd *pTmd;
s32 intFd,intReturnValue;
static char strTmdFileName[43];
    snprintf(strTmdFileName,sizeof(strTmdFileName),"/title/%08x/%08x/content/title.tmd",(u32) MAJOR_NUMBER(intTitleId,u32),(u32) MINOR_NUMBER(intTitleId,u32));
    if ((intFd=ISFS_Open(strTmdFileName,ISFS_OPEN_READ))<0) {
        if ((sTmd=getStoredTmd(intTitleId,&intAlignedBuffer))!=NULL) {
            intTitleId=SIGNATURE_SIZE(sTmd);
            pTmd=SIGNATURE_PAYLOAD(sTmd);
            while (chTmdDatasCount) {
                chTmdDatasCount--;
                switch (TMD_DATAS_LIST[chTmdDatasCount]) {
                    case TMD_CONTENTS_DATA:
                        intReturnValue=TMD_CONTENT_STRUCTURE_SIZE*pTmd->num_contents;
                        break;
                    default:
                        intReturnValue=MAJOR_NUMBER(TMD_DATAS_LIST[chTmdDatasCount],u32);
                        break;
                }
                memcpy(varAlignedTmdDatas[chTmdDatasCount],(void *) sTmd+MINOR_NUMBER(TMD_DATAS_LIST[chTmdDatasCount],u32)+intTitleId,intReturnValue);
                varout=varout+intReturnValue;
            }
            freeVector((void **) &sTmd);
        }
    }
    else {
        if ((intReturnValue=ISFS_Read(intFd,&intAlignedBuffer,sizeof(intAlignedBuffer)))>0) {
            intTitleId=SIGNATURE_SIZE(&intAlignedBuffer);
            while (chTmdDatasCount) {
                chTmdDatasCount--;
                switch (TMD_DATAS_LIST[chTmdDatasCount]) {
                    case TMD_CONTENTS_DATA:
                        if ((intReturnValue=readNandFileDataSegment(intFd,MINOR_NUMBER(TMD_NUM_CONTENTS_DATA,u32)+intTitleId,sizeof(pTmd->num_contents),SEEK_SET,&intTmdContentsCount))>0) {
                            intReturnValue=intTmdContentsCount*TMD_CONTENT_STRUCTURE_SIZE;
                        }
                        else {
                            //TODO
                        }
                        break;
                    default:
                        intReturnValue=MAJOR_NUMBER(TMD_DATAS_LIST[chTmdDatasCount],u32);
                        break;
                }
                if ((intReturnValue=readNandFileDataSegment(intFd,MINOR_NUMBER(TMD_DATAS_LIST[chTmdDatasCount],u32)+intTitleId,intReturnValue,SEEK_SET,varAlignedTmdDatas[chTmdDatasCount]))>0) {
                    varout=varout+intReturnValue;
                }
                else {
                    //TODO
                }
            }
        }
        ISFS_Close(intFd);
    }
    return varout;
}
