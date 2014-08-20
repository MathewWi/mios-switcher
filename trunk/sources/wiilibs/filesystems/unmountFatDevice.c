#include <fat.h>
#include <ogc/disc_io.h>
#include "getDeviceLabel.h"
#include "filesystems.h"
extern enum STORAGE_DEVICES MOUNTED_FAT_DEVICE;
extern struct stFatDevice stStorageDevices[DEVICES_COUNT];
void unmountFatDevice() {
    if (stStorageDevices[MOUNTED_FAT_DEVICE].isMounted) {
        fatUnmount(getDeviceLabel(MOUNTED_FAT_DEVICE));
        stStorageDevices[MOUNTED_FAT_DEVICE].stInterface->shutdown();
        stStorageDevices[MOUNTED_FAT_DEVICE].isMounted=false;
    }
    MOUNTED_FAT_DEVICE=UNKNOWN_STORAGE_DEVICE;
}
