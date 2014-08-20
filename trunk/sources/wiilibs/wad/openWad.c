#include <stdlib.h>
#include "setWadFileMap.h"
#include "openWad.h"
//version finale
FILE *openWad(const char *strWadFileName,struct stWadMap *stWadFileMap) {
FILE *varout=NULL;
    if ((varout=fopen(strWadFileName,"rb"))!=NULL) {
        if (!setWadFileMap(varout,stWadFileMap)) {
            fclose(varout);
            varout=NULL;
        }
    }
    return varout;
}
