#include <stdio.h>
#include <stdarg.h>
//version finale
char *getFormattedString(char *strFormattedString,const char *strFormat,...) {
va_list pArguments;
    va_start(pArguments,strFormat);
    vsprintf(strFormattedString,strFormat,pArguments);
    va_end(pArguments);
    return strFormattedString;
}
