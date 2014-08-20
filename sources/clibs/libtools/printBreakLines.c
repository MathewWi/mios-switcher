#include <stdio.h>
#include <string.h>
#include "../macros.h"
#include "getBreakLineChar.h"
#include "printBreakLines.h"
//version finale
unsigned int printBreakLines(char chBreakChar,size_t intMaxLineSize,const char *strText) {
unsigned int varout=0;
char *chBreakLineChar,*chCurrentOffset=(char *) strText;
size_t intTextSize;
    while (*chCurrentOffset) {
        if ((chBreakLineChar=getBreakLineChar(chCurrentOffset,chBreakChar,intMaxLineSize))<chCurrentOffset) {
            chCurrentOffset=chBreakLineChar+1;
            printf("%.*s%.*s",varout,"\n",intMaxLineSize,chCurrentOffset);
            intTextSize=strlen(chCurrentOffset);
            chCurrentOffset=chCurrentOffset+MIN(intMaxLineSize,intTextSize);
            chCurrentOffset=chCurrentOffset+((char) (*chCurrentOffset==chBreakChar));
        }
        else {
            printf("%.*s%.*s",varout,"\n",chBreakLineChar-chCurrentOffset,chCurrentOffset);
            chCurrentOffset=chBreakLineChar+1;
        }
        varout++;
    }
    return varout;
}
