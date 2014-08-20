#include <string.h>
#include <stdlib.h>
char *basename(const char *strFileName) {
char *varout;
    if ((varout=strrchr(strFileName,'/'))==NULL) {
        return (char *) strFileName;
    }
    else {
        return varout+1;
    }
}
