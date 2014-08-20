#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../clibs/libarray/insertArrayItems.h"
#include "../../clibs/libarray/uniqueArray.h"
#include "../../clibs/libmemory/freeVector.h"
#include "../filesystems/filesystems.h"
#include "../filesystems/getDeviceLabel.h"
#include "../dvd/getDvdGameDiscInfos.h"
#include "../dvd/getDvdGamesList.h"
#include "../dvd/stopDvd.h"
#include "getGcGamesList.h"
struct stDvdDiscInfos *getGcGamesList(unsigned int *intGamesCount,unsigned char chDevicesCount,...) {
static char strGamesPath[GC_DVD_BACKUP_GAMES_PATH_MAXLENGTH+1];
struct stDvdDiscInfos *varout=NULL,*stDeviceGcGamesInfos=NULL;
va_list pArguments;
unsigned int intDeviceGamesCount;
enum STORAGE_DEVICES STORAGE_DEVICE;
    *intGamesCount=0;
    va_start(pArguments,chDevicesCount);
    while (chDevicesCount) {
        chDevicesCount--;
        STORAGE_DEVICE=va_arg(pArguments,enum STORAGE_DEVICES);
        switch (STORAGE_DEVICE) {
            case DVD_STORAGE_DEVICE:
                intDeviceGamesCount=0;
                if ((stDeviceGcGamesInfos=getDvdGameDiscInfos())!=NULL) {
                    if (stDeviceGcGamesInfos->DVD_DISC_TYPE==GC_DVD_DISC) {
                        intDeviceGamesCount=insertArrayItems((void **) &varout,intGamesCount,*intGamesCount,DVD_DISC_INFOS_STRUCTURE_SIZE,1,stDeviceGcGamesInfos);
                    }
                    stDeviceGcGamesInfos=NULL;
                }
                stopDvd();
                if (intDeviceGamesCount>*intGamesCount) {
                    goto FREEANDEXIT;
                }
                break;
            case SD_STORAGE_DEVICE:
            case SDGECKOA_STORAGE_DEVICE:
            case SDGECKOB_STORAGE_DEVICE:
            case USB_STORAGE_DEVICE:
                snprintf(strGamesPath,sizeof(strGamesPath),"%s:%s",getDeviceLabel(STORAGE_DEVICE),GC_DVD_BACKUP_GAMES_PATH);
                if ((stDeviceGcGamesInfos=getDvdGamesList(strGamesPath,STORAGE_DEVICE,GC_DVD_DISC,&intDeviceGamesCount))!=NULL) {
                    intDeviceGamesCount=insertArrayItems((void **) &varout,intGamesCount,*intGamesCount,DVD_DISC_INFOS_STRUCTURE_SIZE,-1*intDeviceGamesCount,stDeviceGcGamesInfos);
                    freeVector((void **) &stDeviceGcGamesInfos);
                    if (intDeviceGamesCount>*intGamesCount) {
                        goto FREEANDEXIT;
                    }
                }
                break;
            default:
                break;
        };
    }
    *intGamesCount=uniqueArray(varout,DVD_DISC_INFOS_STRUCTURE_SIZE,*intGamesCount,0,6);
    EXITFUNCTION:
    va_end(pArguments);
    return varout;
    FREEANDEXIT:
    freeVector((void **) &varout);
    *intGamesCount=0;
    goto EXITFUNCTION;
}
