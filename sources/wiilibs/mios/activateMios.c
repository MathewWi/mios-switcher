#include <stdio.h>
#include <string.h>
#include <ogc/isfs.h>
#include "../nand/createNandFolder.h"
#include "../nand/moveNandFolderContent.h"
#include "../nand/deleteNandDirectory.h"
#include "../titles/titles.h"
#include "activateMios.h"
//version finale
bool activateMios(unsigned char chSelectedMios) {
static char strNandDestPath[38];
static char strTmpPath[14];
    if (chSelectedMios) {
        if (createNandFolder("/tmp/00000101")==ISFS_OK) {
            snprintf(strTmpPath,sizeof(strTmpPath),"/tmp/%08x",MIOS_MINOR_TID+chSelectedMios);
            if (createNandFolder(strTmpPath)==ISFS_OK) {
                snprintf(strNandDestPath,sizeof(strNandDestPath),"/title/00000001/%08x",MIOS_MINOR_TID+chSelectedMios);
                if (moveNandFolderContent(strNandDestPath,"/tmp/00000101")==ISFS_OK) {
                    if (moveNandFolderContent("/title/00000001/00000101",strTmpPath)==ISFS_OK) {
                        if (deleteNandDirectory(strNandDestPath)==ISFS_OK) {
                            if (deleteNandDirectory("/title/00000001/00000101")==ISFS_OK) {
                                if (ISFS_Rename("/tmp/00000101","/title/00000001/00000101")==ISFS_OK) {
                                    if (ISFS_Rename(strTmpPath,strNandDestPath)==ISFS_OK) {
                                        strcat(strNandDestPath,"/00000101.tik");
                                        if (ISFS_Rename("/ticket/00000001/00000101.tik",strNandDestPath)==ISFS_OK) {
                                            return (ISFS_Rename("/title/00000001/00000101/00000101.tik","/ticket/00000001/00000101.tik")==ISFS_OK);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        return true;
    }
    return false;
}
