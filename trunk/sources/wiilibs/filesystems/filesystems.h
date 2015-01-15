#ifndef _FILESYSTEMS_H_
#define _FILESYSTEMS_H_
#include <stdbool.h>
#include <string.h>
#include <ogc/disc_io.h>
#include "../../clibs/macros.h"
#define DEVICES_COUNT 8
#define FAT_DEVICES_COUNT 4
#define SD_STORAGE_DEVICE_NAME "sd"
#define USB_STORAGE_DEVICE_NAME "usb"
#define SDGECKOA_STORAGE_DEVICE_NAME "carda"
#define SDGECKOB_STORAGE_DEVICE_NAME "cardb"
#define SMB_STORAGE_DEVICE_NAME "smb"
#define NAND_STORAGE_DEVICE_NAME ""
#define DVD_STORAGE_DEVICE_NAME "dvd"
enum STORAGE_DEVICES {
    UNKNOWN_STORAGE_DEVICE=0,
    SD_STORAGE_DEVICE=1,
    SDGECKOA_STORAGE_DEVICE=2,
    SDGECKOB_STORAGE_DEVICE=3,
    USB_STORAGE_DEVICE=4,
    SMB_STORAGE_DEVICE=5,
    NAND_STORAGE_DEVICE=6,
    DVD_STORAGE_DEVICE=7,
};
enum {
    STORAGE_DEVICE_NAME_MAXLENGTH=MAX(strlen(SD_STORAGE_DEVICE_NAME),MAX(strlen(USB_STORAGE_DEVICE_NAME),MAX(strlen(SDGECKOA_STORAGE_DEVICE_NAME),MAX(strlen(SDGECKOB_STORAGE_DEVICE_NAME),MAX(strlen(SMB_STORAGE_DEVICE_NAME),MAX(strlen(NAND_STORAGE_DEVICE_NAME),strlen(DVD_STORAGE_DEVICE_NAME)))))))
};
struct stFatDevice {
    const char strLabel[STORAGE_DEVICE_NAME_MAXLENGTH+1];
    const DISC_INTERFACE *stInterface;
    bool isMounted;
};
#endif