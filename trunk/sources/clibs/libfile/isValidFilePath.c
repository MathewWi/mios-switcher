#include <stdlib.h>
#include "../libstring/getSplitStrings.h"
#include "../libmemory/freeRecursiveVector.h"
#include "isValidFileName.h"
#include "isValidFilePath.h"
bool isValidFilePath(const char *strFilePath) {
bool varout;
char **strSplitItems=NULL,*chInvalidChar;
unsigned int intItemsCount=-1,i;
    if ((strSplitItems=getSplitStrings(strFilePath+(char)(*strFilePath=='/'),"/",&intItemsCount))==NULL) {
        varout=false;
    }
    else {
        varout=true;
        i=intItemsCount;
        while ((i) && (varout)) {
            i--;
            if (*strSplitItems[i]) {
                varout=isValidFileName(strSplitItems[i],&chInvalidChar);
            }
            else {
                varout=(i==intItemsCount-1);
            }
        }
        freeRecursiveVector((void ***) &strSplitItems,intItemsCount);
    }
    return varout;
}
