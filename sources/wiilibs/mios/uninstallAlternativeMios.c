#include <stdio.h>
#include <ogc/isfs.h>
#include "../../clibs/libmemory/permutePointers.h"
#include "../titles/uninstallTitle.h"
#include "../nand/createNandFolder.h"
#include "../nand/deleteNandDirectory.h"
#include "../nand/moveNandFolderContent.h"
#include "activateMios.h"
#include "uninstallAlternativeMios.h"
bool uninstallAlternativeMios(unsigned char chSelectedMios,struct stTitleInfos **stInstalledMiosInfos,unsigned char *chInstalledMiosCount) {
static char strNandSrcPath[25];
    if (chSelectedMios<*chInstalledMiosCount) {
        if (activateMios(chSelectedMios)) {
            permutePointers((void **) &stInstalledMiosInfos[0],(void **) &stInstalledMiosInfos[chSelectedMios]);
            if (uninstallTitle(MIOS_TID,false)>-1) {
                if ((*chInstalledMiosCount=*chInstalledMiosCount-1)) {
                    if (createNandFolder("/tmp/00000101")==ISFS_OK) {
                        snprintf(strNandSrcPath,sizeof(strNandSrcPath),"/title/00000001/%08x",MIOS_MINOR_TID+*chInstalledMiosCount);
                        if (moveNandFolderContent(strNandSrcPath,"/tmp/00000101")==ISFS_OK) {
                            if (deleteNandDirectory(strNandSrcPath)==ISFS_OK) {
                                if (ISFS_Rename("/tmp/00000101","/title/00000001/00000101")==ISFS_OK) {
                                    permutePointers((void **) &stInstalledMiosInfos[0],(void **) &stInstalledMiosInfos[*chInstalledMiosCount]);
                                    return (ISFS_Rename("/title/00000001/00000101/00000101.tik","/ticket/00000001/00000101.tik")==ISFS_OK);
                                }
                            }
                        }
                    }
                }
                else {
                    return true;
                }
            }
        }
    }
    return false;
}
