#include <string.h>
#include <stdlib.h>
#include "../libtools/getBreakLineChar.h"
#include "../libmemory/getCharsVector.h"
#include "../macros.h"
#include "getBreakString.h"
//version finale
char *getBreakString(const char *strValue,char chBreakChar,size_t intMaxStringSize) {
char *varout=NULL,*chBreakCharacter;
size_t intStringSize;
    if ((chBreakCharacter=getBreakLineChar(strValue,chBreakChar,intMaxStringSize))<strValue) {
        intStringSize=strlen(strValue);
        intMaxStringSize=MIN(intMaxStringSize,intStringSize);
        if ((varout=getCharsVector(intMaxStringSize+1,intMaxStringSize,1,0))!=NULL) {
            strncpy(varout,strValue,intMaxStringSize);
        }
    }
    else {
        intMaxStringSize=chBreakCharacter-strValue;
        if ((varout=getCharsVector(intMaxStringSize+1,intMaxStringSize,1,0))!=NULL) {
            strncpy(varout,strValue,intMaxStringSize);
        }
    }
    return varout;
}
