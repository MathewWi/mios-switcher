#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ogc/es.h>
#include "../../clibs/libfile/basename.h"
#include "../../clibs/libmemory/reallocBuffer.h"
#include "../../clibs/libmemory/libmemory.h"
#include "../../clibs/libmemory/freeVector.h"
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "../../clibs/macros.h"
#include "../../clibs/clibs.h"
#include "../nand/haveNandAccess.h"
#include "../nand/getNandFolderContent.h"
#include "../titles/readStoredTmdDatas.h"
#include "../titles/titles.h"
#include "getTitles.h"
//version finale
u64 *getTitles(u32 *intTitlesCount) {
u64 *varout=NULL;
int intNandTitleFolderItemsCount;
s32 intReturnValue;
char **strNandTitleFolderContent=NULL,*chUnexpectedChar;
static u64 intTitleId __attribute__((aligned(0x20)));
static enum TMD_DATAS TMD_DATAS_LIST[1]={TMD_TITLE_ID_DATA};
static void *varAlignedTmdDatas[1]={&intTitleId};
    if (haveNandAccess()) {
        if ((strNandTitleFolderContent=getNandFolderContent("/title",true,&intNandTitleFolderItemsCount))==NULL) {
            goto GET_TITLES_BY_ES_COMMANDS;
        }
        else {
            *intTitlesCount=0;
            if ((varout=malloc(intNandTitleFolderItemsCount*LONGINT_TYPE_SIZE))==NULL) {
                //TODO
            }
            else {
                for (intReturnValue=0;intReturnValue<intNandTitleFolderItemsCount;intReturnValue++) {
                    if (!strcmp("title.tmd",basename(strNandTitleFolderContent[intReturnValue]))) {
                        varout[*intTitlesCount]=MAJOR_MINOR_NUMBER(strtoul(strNandTitleFolderContent[intReturnValue]+7,&chUnexpectedChar,16),strtoul(strNandTitleFolderContent[intReturnValue]+16,&chUnexpectedChar,16),u32);
                        if (readStoredTmdDatas(varout[*intTitlesCount],TMD_DATAS_LIST,varAlignedTmdDatas,1)) {
                            if (intTitleId==varout[*intTitlesCount]) {
                                *intTitlesCount=*intTitlesCount+1;
                            }
                        }
                        else {
                            //TODO
                        }
                    }
                }
                reallocBuffer((void **) &varout,*intTitlesCount*LONGINT_TYPE_SIZE,0);
            }
            freeRecursiveVector((void ***) &strNandTitleFolderContent,intNandTitleFolderItemsCount);
        }
    }
    else {
        GET_TITLES_BY_ES_COMMANDS:
        if ((intReturnValue=ES_GetNumTitles(intTitlesCount))<0) {
            //TODO
        }
        else {
            if (*intTitlesCount==0) {
                //TODO
            }
            else {
                if ((varout=GET_ALIGNED_MEMORY(*intTitlesCount*LONGINT_TYPE_SIZE,32))==NULL) {
                    //TODO
                }
                else {
                    if ((intReturnValue=ES_GetTitles(varout,*intTitlesCount))<0) {
                        //TODO
                        freeVector((void **) &varout);
                    }
                }
            }
        }
    }
    return varout;
}
