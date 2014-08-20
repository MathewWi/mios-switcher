#include <string.h>
#include <stddef.h>
#include "getAppArguments.h"
//version finale
unsigned int getAppArguments(char **strAppArguments,unsigned int intAppArgumentsCount,struct stAppArgument *stAppArguments,unsigned int intScanArgumentsCount) {
unsigned int varout=0,i;
size_t intSwitchSize;
    while (intAppArgumentsCount) {
        intAppArgumentsCount--;
        for (i=0;i<intScanArgumentsCount;i++) {
            intSwitchSize=strlen(stAppArguments[i].strArgumentSwitch);
            if (!strncmp(stAppArguments[i].strArgumentSwitch,strAppArguments[intAppArgumentsCount],intSwitchSize)) {
                stAppArguments[i].strArgumentValue=strAppArguments[intAppArgumentsCount]+intSwitchSize;
                varout++;
            }
        }
    }
    return varout;
}
