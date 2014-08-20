#include <stdio.h>
#include <string.h>
#include <ogc/isfs.h>
#include "../../clibs/libfile/dirname.h"
#include "nand.h"
#include "moveNandFolderContent.h"
#include "deleteNandDirectory.h"
#include "renameNandFolder.h"
//version finale
extern char strNandPath[NAND_PATH_MAXLENGTH];
s32 renameNandFolder(const char *strFolderPath,const char *strNewFolderName) {
s32 varout;
    snprintf(strNandPath,NAND_PATH_MAXLENGTH,"%s/%s",dirname(strcpy(strNandPath,strFolderPath)),strNewFolderName);
    if ((varout=ISFS_CreateDir(strNandPath,0,ISFS_OPEN_RW,ISFS_OPEN_RW,ISFS_OPEN_RW))<0) {
        //TODO
    }
    else {
        varout=moveNandFolderContent(strFolderPath,strNandPath);
        deleteNandDirectory(strFolderPath);
    }
    return varout;
}
