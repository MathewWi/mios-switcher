#include <stdarg.h>
#include <stdio.h>
#include "../video/saveCursorPosition.h"
#include "../video/setCursorPosition.h"
#include "getTextBoxColumn.h"
#include "getTextBoxRow.h"
#include "printLocatedText.h"
//version finale
int printLocatedText(u8 chRow,u8 chColumn,struct stConsoleCursorLocation *stTexteLocation,const char *strTexteFormat,...) {
int varout;
va_list pArguments;
    saveCursorPosition();
    stTexteLocation->intColumn=getTextBoxColumn(chColumn);
    stTexteLocation->intRow=getTextBoxRow(chRow);
    setCursorPosition(stTexteLocation->intRow,stTexteLocation->intColumn);
    va_start(pArguments,strTexteFormat);
    varout=vprintf(strTexteFormat,pArguments);
    va_end(pArguments);
    saveCursorPosition();
    return varout;
}
