#include "../../clibs/libmemory/freeVector.h"
#include "closeWad.h"
//version finale
void closeWad(FILE *fpwad,struct stWadMap *stWadFileMap) {
    freeVector((void **) &stWadFileMap->stTmdContents);
    fclose(fpwad);
}
