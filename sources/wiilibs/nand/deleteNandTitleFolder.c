#include <stdio.h>
#include "../../clibs/macros.h"
#include "nand.h"
#include "deleteNandDirectory.h"
#include "deleteNandTitleFolder.h"
//version finale
extern char strNandPath[NAND_PATH_MAXLENGTH];
s32 deleteNandTitleFolder(u64 intTitleId) {
    snprintf(strNandPath,NAND_PATH_MAXLENGTH,"/title/%08x/%08x",(u32) MAJOR_NUMBER(intTitleId,u32),(u32) MINOR_NUMBER(intTitleId,u32));
    return deleteNandDirectory(strNandPath);
}
