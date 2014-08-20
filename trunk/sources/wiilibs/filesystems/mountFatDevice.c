#include <stdarg.h>
#include <unistd.h>
#include <fat.h>
#include <ogc/disc_io.h>
#include "getDeviceLabel.h"
#include "unmountFatDevice.h"
#include "mountFatDevice.h"
//version finale
extern enum STORAGE_DEVICES MOUNTED_FAT_DEVICE;
extern struct stFatDevice stStorageDevices[DEVICES_COUNT];
enum STORAGE_DEVICES mountFatDevice(unsigned char chStorageDevicesCount,...) {
va_list pArguments;
    unmountFatDevice();
    va_start(pArguments,chStorageDevicesCount);
    while ((chStorageDevicesCount) && (MOUNTED_FAT_DEVICE==UNKNOWN_STORAGE_DEVICE)) {
        chStorageDevicesCount--;
        if ((MOUNTED_FAT_DEVICE=va_arg(pArguments,enum STORAGE_DEVICES))>FAT_DEVICES_COUNT) {
            MOUNTED_FAT_DEVICE=UNKNOWN_STORAGE_DEVICE;
        }
        else {
            if (MOUNTED_FAT_DEVICE!=UNKNOWN_STORAGE_DEVICE) {
                stStorageDevices[MOUNTED_FAT_DEVICE].stInterface->startup();
                stStorageDevices[MOUNTED_FAT_DEVICE].isMounted=((stStorageDevices[MOUNTED_FAT_DEVICE].stInterface->isInserted()) && (fatMountSimple(getDeviceLabel(MOUNTED_FAT_DEVICE),stStorageDevices[MOUNTED_FAT_DEVICE].stInterface)));
                if (!stStorageDevices[MOUNTED_FAT_DEVICE].isMounted) {
                    stStorageDevices[MOUNTED_FAT_DEVICE].stInterface->shutdown();
                    MOUNTED_FAT_DEVICE=UNKNOWN_STORAGE_DEVICE;
                }
            }
        }
    }
    va_end(pArguments);
    return MOUNTED_FAT_DEVICE;
}
