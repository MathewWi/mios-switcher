#include <ogc/es.h>
#include <gctypes.h>
#include "../../clibs/libfile/readFileDataSegment.h"
#include "../../clibs/macros.h"
#include "readWadTmdDatas.h"
//version finale
size_t readWadTmdDatas(FILE *fpwad,struct stWadMap *stWadFileMap,enum TMD_DATAS *TMD_DATAS_LIST,void **varTmdDatas,unsigned char chTmdDatasCount) {
size_t varout=0,intTmdDataSize;
signed_blob *sTmd=&intTmdDataSize;
unsigned int intOffsetTmdData;
    if (readFileDataSegment(fpwad,stWadFileMap->intOffsetTmdData,sizeof(signed_blob),SEEK_SET,sTmd)) {
        intOffsetTmdData=stWadFileMap->intOffsetTmdData+SIGNATURE_SIZE(sTmd);
        while (chTmdDatasCount) {
            chTmdDatasCount--;
            switch (TMD_DATAS_LIST[chTmdDatasCount]) {
                case TMD_CONTENTS_DATA:
                    if (readFileDataSegment(fpwad,MINOR_NUMBER(TMD_NUM_CONTENTS_DATA,u32)+intOffsetTmdData,MAJOR_NUMBER(TMD_NUM_CONTENTS_DATA,u32),SEEK_SET,sTmd)) {
                        intTmdDataSize=*((u16 *) sTmd)*TMD_CONTENT_STRUCTURE_SIZE;
                    }
                    else {
                        intTmdDataSize=0;
                    }
                    break;
                default:
                    intTmdDataSize=MAJOR_NUMBER(TMD_DATAS_LIST[chTmdDatasCount],u32);
                    break;
            }
            if ((intTmdDataSize=readFileDataSegment(fpwad,MINOR_NUMBER(TMD_DATAS_LIST[chTmdDatasCount],u32)+intOffsetTmdData,intTmdDataSize,SEEK_SET,varTmdDatas[chTmdDatasCount]))) {
                varout=varout+intTmdDataSize;
            }
        }
    }
    return varout;
}
