#include <stdio.h>
#include "../../clibs/macros.h"
#include "nand.h"
#include "existNandFile.h"
#include "existNandTitle.h"
//version finale
extern char strNandPath[NAND_PATH_MAXLENGTH];
bool existNandTitle(u64 intTitleId) {
    snprintf(strNandPath,NAND_PATH_MAXLENGTH,"/title/%08x/%08x/content/title.tmd",(u32) MAJOR_NUMBER(intTitleId,u32),(u32) MINOR_NUMBER(intTitleId,u32));
    return existNandFile(strNandPath);
}
