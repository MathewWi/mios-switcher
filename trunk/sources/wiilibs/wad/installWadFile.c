#include <stdio.h>
#include <stdlib.h>
#include "openWad.h"
#include "wad.h"
#include "installWadFile2.h"
#include "installWadFile.h"
s32 installWadFile(const char *strWadFilename) {
FILE *fpwad;
struct stWadMap stWadFileMap;
s32 varout=-1;
    if ((fpwad=openWad(strWadFilename,&stWadFileMap))!=NULL) {
        varout=installWadFile2(fpwad,&stWadFileMap);
        fclose(fpwad);
    }
    return varout;
}
