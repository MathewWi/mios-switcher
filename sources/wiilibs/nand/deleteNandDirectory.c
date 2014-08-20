#include <ogc/isfs.h>
#include "deleteNandDirectoryContent.h"
#include "deleteNandDirectory.h"
//version finale
s32 deleteNandDirectory(const char *strDirectoryPath) {
s32 varout;
    if ((varout=deleteNandDirectoryContent(strDirectoryPath))<0) {

    }
    else {
        if ((varout=ISFS_Delete(strDirectoryPath))<0) {

        }
    }
    return varout;
}
