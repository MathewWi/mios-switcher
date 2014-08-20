#include <stdio.h>
#include <stdarg.h>
//version finale
unsigned int printRepeatString(unsigned int intRepeatsCount,const char *strFormatValue,...) {
unsigned int varout=0;
va_list pArguments;
    while (intRepeatsCount) {
        intRepeatsCount--;
        va_start(pArguments,strFormatValue);
        varout=varout+vprintf(strFormatValue,pArguments);
        va_end(pArguments);
    }
    return varout;
}
