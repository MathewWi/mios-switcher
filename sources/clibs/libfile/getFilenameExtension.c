#include <string.h>
#include <stdlib.h>
char *getFilenameExtension(const char *strFilename) {
char *varout;
    if ((varout=strrchr(strFilename,'.'))==NULL) {
        return (char *) &strFilename[strlen(strFilename)];
    }
    else {
        return varout+1;
    }
}
