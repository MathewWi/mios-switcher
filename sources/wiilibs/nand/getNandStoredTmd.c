#include <stdio.h>
#include <stdlib.h>
#include "../../clibs/macros.h"
#include "nand.h"
#include "getNandFileContent.h"
#include "getNandStoredTmd.h"
//version finale
extern char strNandPath[NAND_PATH_MAXLENGTH];
signed_blob *getNandStoredTmd(u64 intTitleId,size_t *intTmdSize) {
signed_blob *varout=NULL;
    snprintf(strNandPath,NAND_PATH_MAXLENGTH,"/title/%08x/%08x/content/title.tmd",(u32) MAJOR_NUMBER(intTitleId,u32),(u32) MINOR_NUMBER(intTitleId,u32));
    if ((varout=getNandFileContent(strNandPath,intTmdSize))==NULL) {
        //TODO
    }
    return varout;
}
