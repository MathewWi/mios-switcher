#include <ogc/isfs.h>
#include "../nand/haveNandAccess.h"
#include "filesystems.h"
#include "mountNandFs.h"
//version finale
extern struct stFatDevice stStorageDevices[DEVICES_COUNT];
extern bool haveNANDAccess;
bool mountNandFs() {
    if (!stStorageDevices[NAND_STORAGE_DEVICE].isMounted) {
        if (ISFS_Initialize()==ISFS_OK) {
            stStorageDevices[NAND_STORAGE_DEVICE].isMounted=true;
            haveNANDAccess=haveNandAccess();
        }
    }
    return stStorageDevices[NAND_STORAGE_DEVICE].isMounted;
}
