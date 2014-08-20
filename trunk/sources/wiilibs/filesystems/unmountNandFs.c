#include <stdbool.h>
#include <ogc/isfs.h>
#include "filesystems.h"
//version finale
extern struct stFatDevice stStorageDevices[DEVICES_COUNT];
extern bool haveNANDAccess;
void unmountNandFs() {
    if (stStorageDevices[NAND_STORAGE_DEVICE].isMounted) {
        ISFS_Deinitialize();
        stStorageDevices[NAND_STORAGE_DEVICE].isMounted=false;
        haveNANDAccess=false;
    }
}
