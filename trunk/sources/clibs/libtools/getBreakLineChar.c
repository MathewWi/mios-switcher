#include <string.h>
#include <stdlib.h>
#include "getBreakLineChar.h"
//version finale
char *getBreakLineChar(const char *strValue,char chBreakChar,size_t intMaxLineSize) {
char *varout=(char *) strValue,*chCurrentOffset;
    if (strlen(strValue)>intMaxLineSize) {
        intMaxLineSize++;
        while ((chCurrentOffset=strchr(varout,chBreakChar))!=NULL) {
            if (chCurrentOffset-varout<intMaxLineSize) {
                chCurrentOffset=chCurrentOffset+1;
                intMaxLineSize=intMaxLineSize-(chCurrentOffset-varout);
                varout=chCurrentOffset;
            }
            else {
                break;
            }
        }
    }
    return varout-1;
}
