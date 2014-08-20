#include <string.h>
//version finale
char *devicename(char *strPath) {
char *chChar;
    if ((chChar=strchr(strPath,':'))==NULL) {
        *strPath=0;
    }
    else {
        *chChar=0;
    }
    return strPath;
}
