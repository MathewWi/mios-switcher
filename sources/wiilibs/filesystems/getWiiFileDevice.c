#include <string.h>
#include "../../clibs/libfile/getDeviceName.h"
#include "getDeviceLabel.h"
#include "getWiiFileDevice.h"
enum STORAGE_DEVICES getWiiFileDevice(const char *strFilename) {
unsigned char i;
char *strDevicename=getDeviceName(strFilename);
    if (*strDevicename) {
        for (i=1;i<DEVICES_COUNT;i++) {
            if (!strcmp(strDevicename,getDeviceLabel(i))) {
                return i;
            }
        }
    }
    return UNKNOWN_STORAGE_DEVICE;
}
