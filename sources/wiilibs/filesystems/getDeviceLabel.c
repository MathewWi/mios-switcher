#include "getDeviceLabel.h"
extern struct stFatDevice stStorageDevices[DEVICES_COUNT];
const char *getDeviceLabel(enum STORAGE_DEVICES STORAGE_DEVICE) {
    return (STORAGE_DEVICE<DEVICES_COUNT)?stStorageDevices[STORAGE_DEVICE].strLabel:stStorageDevices[UNKNOWN_STORAGE_DEVICE].strLabel;
}
