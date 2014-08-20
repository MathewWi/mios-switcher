#include <stdio.h>
#include "../../clibs/macros.h"
#include "deleteNandFile.h"
#include "nand.h"
#include "deleteNandTitleTicket.h"
//version finale
extern char strNandPath[NAND_PATH_MAXLENGTH];
s32 deleteNandTitleTicket(u64 intTitleId) {
    snprintf(strNandPath,sizeof(strNandPath),"/ticket/%08x/%08x.tik",(u32) MAJOR_NUMBER(intTitleId,u32),(u32) MINOR_NUMBER(intTitleId,u32));
    return deleteNandFile(strNandPath);
}
