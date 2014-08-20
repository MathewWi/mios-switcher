#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>
#include "../../clibs/libfile/getFolderContent.h"
#include "../../clibs/libfile/isDirectory.h"
#include "../../clibs/libfile/basename.h"
#include "../../clibs/libfile/getFilenameExtension.h"
#include "../../clibs/libmemory/reallocBuffer.h"
#include "../../clibs/libmemory/freeRecursiveVector.h"
#include "../filesystems/mountFatDevice.h"
#include "../filesystems/unmountFatDevice.h"
#include "readDvdGameInfos.h"
#include "getDvdGamesList.h"
struct stDvdDiscInfos *getDvdGamesList(const char *strGamesPath,enum STORAGE_DEVICES STORAGE_DEVICE,enum DVD_DISC_TYPES DVD_DISC_TYPE,unsigned int *intGamesCount) {
struct stDvdDiscInfos *varout=NULL;
char **strGamesFolderContent=NULL;
unsigned int intGameFoldersCount,i;
FILE *fhGameBootFile;
size_t intGamesPathSize;
    *intGamesCount=0;
    if (mountFatDevice(1,STORAGE_DEVICE)==STORAGE_DEVICE) {
        if ((strGamesFolderContent=getFolderContent(strGamesPath,false,&intGameFoldersCount))!=NULL) {
            if ((varout=malloc(intGameFoldersCount*DVD_DISC_INFOS_STRUCTURE_SIZE))!=NULL) {
                intGamesPathSize=strlen(strGamesPath);
                intGamesPathSize=intGamesPathSize+(char)(strGamesPath[intGamesPathSize-1]!='/');
                for (i=0;i<intGameFoldersCount;i++) {
                    if (isDirectory(strGamesFolderContent[i])) {
                        if ((varout[*intGamesCount].STORAGE_DEVICE=intGamesPathSize+6)==strlen(strGamesFolderContent[i])) {
                            if (reallocBuffer((void **) &strGamesFolderContent[i],varout[*intGamesCount].STORAGE_DEVICE+13,0)!=NULL) {
                                strcat(strGamesFolderContent[i],"/game.iso");
                                if ((fhGameBootFile=fopen(strGamesFolderContent[i],"rb"))==NULL) {
                                    strcpy(strGamesFolderContent[i]+varout[*intGamesCount].STORAGE_DEVICE+1,"sys/boot.bin");
                                    if ((fhGameBootFile=fopen(strGamesFolderContent[i],"rb"))==NULL) {
                                        continue;
                                    }
                                    else {
                                        varout[*intGamesCount].DVD_GAME_FORMAT=FST_GAME_FORMAT;
                                    }
                                }
                                else {
                                    varout[*intGamesCount].DVD_GAME_FORMAT=ISO_GAME_FORMAT;
                                }
                                varout[*intGamesCount].DVD_DISC_TYPE=readDvdGameInfos(fhGameBootFile,0,&varout[*intGamesCount]);
                                if ((DVD_DISC_TYPE & varout[*intGamesCount].DVD_DISC_TYPE)) {
                                    if (!strncmp(varout[*intGamesCount].strDiscID,strGamesFolderContent[i]+intGamesPathSize,6)) {
                                        varout[*intGamesCount].STORAGE_DEVICE=STORAGE_DEVICE;
                                        *intGamesCount=*intGamesCount+1;
                                    }
                                }
                                fclose(fhGameBootFile);
                            }
                        }
                    }
                    else {
                        if (strlen(strGamesFolderContent[i]+intGamesPathSize)==11) {
                            if (!strcmp(getFilenameExtension(strGamesFolderContent[i]),"wbfs")) {
                                if ((fhGameBootFile=fopen(strGamesFolderContent[i],"rb"))==NULL) {
                                    varout[*intGamesCount].DVD_DISC_TYPE=readDvdGameInfos(fhGameBootFile,0x200,&varout[*intGamesCount]);
                                    if ((DVD_DISC_TYPE & varout[*intGamesCount].DVD_DISC_TYPE)) {
                                        if (!strncmp(varout[*intGamesCount].strDiscID,strGamesFolderContent[i]+intGamesPathSize,6)) {
                                            varout[*intGamesCount].STORAGE_DEVICE=STORAGE_DEVICE;
                                            *intGamesCount=*intGamesCount+1;
                                        }
                                    }
                                    fclose(fhGameBootFile);
                                }
                            }
                        }
                    }
                }
                reallocBuffer((void **) &varout,*intGamesCount*DVD_DISC_INFOS_STRUCTURE_SIZE,0);
            }
            freeRecursiveVector((void ***) &strGamesFolderContent,intGameFoldersCount);
        }
        unmountFatDevice();
    }
    return varout;
}
