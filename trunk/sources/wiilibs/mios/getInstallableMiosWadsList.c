#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../clibs/libarray/getArrayMemoryItemIndex.h"
#include "../../clibs/libfile/getFolderContent.h"
#include "../../clibs/libfile/getFilenameExtension.h"
#include "../../clibs/libfile/isDirectory.h"
#include "../../clibs/libmemory/reallocBuffer.h"
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "../../clibs/libmemory/getClonedBuffer.h"
#include "../wad/openWad.h"
#include "../wad/closeWad.h"
#include "../wad/readWadTmdDatas.h"
#include "../wad/wad.h"
#include "isMiosInstalled.h"
#include "getInstallableMiosWadsList.h"
struct stListItem *getInstallableMiosWadsList(const char *strWadsFolder,struct stTitleInfos *stKnownMiosInfos,unsigned int intKnownMiosCount,struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount,unsigned int *intWadsCount) {
struct stListItem *varout=NULL;
char **strFolderItems=NULL;
unsigned int intItemsCount;
FILE *fpwad;
struct stWadMap stWadFileMap={0,0,0,0,0,0,0,0,0,NULL,0,0};
static enum TMD_DATAS TMD_DATAS_LIST[2]={TMD_TITLE_ID_DATA,GET_CONTENT_ENUM_TMD_DATA(1,TMD_CONTENT_HASH_DATA)};
static struct stTitleInfos stWadMiosInfos;
static void *varTmdDatas[2]={&stWadMiosInfos.intTitleId,stWadMiosInfos.stIdentificationModule.chModuleHash};
    *intWadsCount=0;
    if ((strFolderItems=getFolderContent(strWadsFolder,false,&intItemsCount))!=NULL) {
        if ((varout=getDynamicMemory(intItemsCount*LIST_ITEM_STRUCTURE_SIZE))!=NULL) {
            while (intItemsCount) {
                intItemsCount--;
                if (!stricmp(getFilenameExtension(strFolderItems[intItemsCount]),"wad")) {
                    if (!isDirectory(strFolderItems[intItemsCount])) {
                        if ((fpwad=openWad(strFolderItems[intItemsCount],&stWadFileMap))!=NULL) {
                            if (readWadTmdDatas(fpwad,&stWadFileMap,TMD_DATAS_LIST,varTmdDatas,2)==sizeof(stWadMiosInfos.intTitleId)+sizeof(stWadMiosInfos.stIdentificationModule.chModuleHash)) {
                                if (stWadMiosInfos.intTitleId==MIOS_TID) {
                                    if (!isMiosInstalled(stWadMiosInfos.stIdentificationModule.chModuleHash,stInstalledMiosInfos,chInstalledMiosCount)) {
                                        if ((stWadMiosInfos.intTitleId=getArrayMemoryItemIndex(&varout[0].varMetaDatas,*intWadsCount,stWadMiosInfos.stIdentificationModule.chModuleHash,-20,LIST_ITEM_STRUCTURE_SIZE,false))==*intWadsCount) {
                                            if ((stWadMiosInfos.intTitleId=getArrayMemoryItemIndex(stKnownMiosInfos[0].stIdentificationModule.chModuleHash,intKnownMiosCount,stWadMiosInfos.stIdentificationModule.chModuleHash,20,TITLE_INFOS_STRUCTURE_SIZE,false))<intKnownMiosCount) {
                                                varout[*intWadsCount].strLabel=strdup(strFolderItems[intItemsCount]);
                                                varout[*intWadsCount].varMetaDatas=getClonedBuffer(stWadMiosInfos.stIdentificationModule.chModuleHash,20,0);
                                                varout[*intWadsCount].blnMarked=false;
                                                *intWadsCount=*intWadsCount+1;
                                            }
                                        }
                                    }
                                }
                            }
                            closeWad(fpwad,&stWadFileMap);
                        }
                    }
                }
            }
            reallocBuffer((void **) &varout,*intWadsCount*LIST_ITEM_STRUCTURE_SIZE,0);
        }
        freeRecursiveVector((void ***) &strFolderItems,intItemsCount);
    }
    return varout;
}
