#include <stdlib.h>
#include <string.h>
#include "../libmemory/permutePointers.h"
#include "../libmath/isInRange.h"
#include "../clibs.h"
#include "isDirectory.h"
#include "getFileSize.h"
#include "getFilenameExtension.h"
#include "filterFolderContent.h"
unsigned int filterFolderContent(char **strFolderContent,unsigned int intFolderItemsCount,const char *strFileExtension,size_t intMinFileSize,size_t intMaxFileSize) {
unsigned int varout=0;
    if (strFileExtension==NULL) {
        while (varout<intFolderItemsCount) {
            if (isDirectory(strFolderContent[varout])) {
                varout++;
            }
            else {
                intFolderItemsCount--;
                permutePointers((void **) &strFolderContent[varout],(void **) &strFolderContent[intFolderItemsCount]);
            }
        }
    }
    else {
        while (varout<intFolderItemsCount) {
            if (!strcmp(getFilenameExtension(strFolderContent[varout]),strFileExtension)) {
                if (!isInRange(getFileSize(strFolderContent[varout]),intMinFileSize,intMaxFileSize,true,true)) {
                    varout++;
                    continue;
                }
            }
            intFolderItemsCount--;
            permutePointers((void **) &strFolderContent[varout],(void **) &strFolderContent[intFolderItemsCount]);
        }
    }
    return varout;
}
