#include <sdcard/wiisd_io.h>
#include <di/di.h>
#include <sdcard/gcsd.h>
#include <ogc/usbstorage.h>
#include "filesystems.h"
struct stFatDevice stStorageDevices[DEVICES_COUNT]={{"",NULL,false},{SD_STORAGE_DEVICE_NAME,&__io_wiisd,false},{SDGECKOA_STORAGE_DEVICE_NAME,&__io_gcsda,false},{SDGECKOB_STORAGE_DEVICE_NAME,&__io_gcsdb,false},{USB_STORAGE_DEVICE_NAME,&__io_usbstorage,false},{SMB_STORAGE_DEVICE_NAME,NULL,false},{NAND_STORAGE_DEVICE_NAME,NULL,false},{DVD_STORAGE_DEVICE_NAME,&__io_wiidvd,false}};
enum STORAGE_DEVICES MOUNTED_FAT_DEVICE=UNKNOWN_STORAGE_DEVICE;
