#include <ogc/isfs.h>
#include "existNandFile.h"
#include "deleteNandFile.h"
//version finale
s32 deleteNandFile(const char *strFileName) {
    if (existNandFile(strFileName)) {
        return ISFS_Delete(strFileName);
    }
    else {
        return ISFS_OK;
    }
}
