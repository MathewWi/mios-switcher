#include <stdio.h>
#include "devicename.h"
char *getDeviceName(const char *strFilename) {
static char varout[10];
    snprintf(varout,sizeof(varout),"%s",strFilename);
    return devicename(varout);
}
