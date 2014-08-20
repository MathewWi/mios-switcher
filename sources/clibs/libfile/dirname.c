#include <string.h>
#include <stdlib.h>
//version finale
char *dirname(char *strFileName) {
char *chLastSlashOffset;
    if ((chLastSlashOffset=strrchr(strFileName,'/'))==NULL) {
        *strFileName=0;
    }
    else {
        *chLastSlashOffset=0;
    }
    return strFileName;
}
