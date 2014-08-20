#include <string.h>
#include <stddef.h>
#include "../libarray/getArrayItemCount.h"
#include "../libmemory/freeVector.h"
#include "../macros.h"
#include "../clibs.h"
#include "isValidFileName.h"
bool isValidFileName(const char *strFileName,char **chInvalidChar) {
static const char *strReservedFileNames[23]={"CLOCK$","AUX","CON","NUL","PRN","COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9","LPT1","LPT2","LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9"};
bool varout=false;
size_t intFilenameSize;
unsigned int *intArrayItemIndexes=NULL;
    if ((intFilenameSize=strlen(strFileName))>0) {
        if (*strFileName==' ') {
            *chInvalidChar=(char *) strFileName;
        }
        else {
            *chInvalidChar=(char *) &strFileName[intFilenameSize-1];
            if (*(*chInvalidChar)!=' ') {
                if ((*chInvalidChar=strpbrk(strFileName,"\\/:*?\"<>|"))==NULL) {
                    if (getArrayItemCount(strFileName,intFilenameSize,".",1,false,&intArrayItemIndexes)==intFilenameSize) {
                        *chInvalidChar=(char *) strFileName;
                    }
                    else {
                        varout=true;
                        intFilenameSize=STATIC_ARRAY_SIZE(strReservedFileNames);
                        while ((intFilenameSize) && (varout)) {
                            intFilenameSize--;
                            if (!stricmp(strFileName,strReservedFileNames[intFilenameSize])) {
                                varout=false;
                                *chInvalidChar=(char *) strFileName;
                            }
                        }
                        freeVector((void **) &intArrayItemIndexes);
                    }
                }
            }
        }
    }
    return varout;
}
