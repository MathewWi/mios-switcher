#include <string.h>
#include <stdlib.h>
#include "../macros.h"
#include "getDynamicMemory.h"
#include "getCharsVector.h"
//version finale
char *getCharsVector(size_t intSizeVect,unsigned int intInitOffset,size_t intInitSize,char chInitValue) {
char *varout=NULL;
    if ((varout=getDynamicMemory(intSizeVect))==NULL) {
        //todo
    }
    else {
        if (intInitOffset<intSizeVect) {
            intSizeVect=intSizeVect-intInitOffset;
            memset(&varout[intInitOffset],chInitValue,MIN(intSizeVect,intInitSize));
        }
    }
	return varout;
}
