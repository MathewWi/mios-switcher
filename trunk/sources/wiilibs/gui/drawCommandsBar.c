#include <stdio.h>
#include <ogc/consol.h>
#include "../../clibs/libtools/printRepeatString.h"
#include "../../clibs/macros.h"
#include "../video/saveCursorPosition.h"
#include "../video/setCursorPosition.h"
#include "../video/resetSavedCursorPosition.h"
#include "../video/clearConsoleArea.h"
#include "drawCommandsBar.h"
//version finale
void drawCommandsBar(unsigned char chCommandsCount,bool blnStatusBar,struct stCommandsBar *stCommandsBarSettings) {
int intConsoleColumnsCount,intConsoleRowsCount;
    CON_GetMetrics(&intConsoleColumnsCount,&intConsoleRowsCount);
    stCommandsBarSettings->chCommandsCount=chCommandsCount;
    stCommandsBarSettings->chCommandItemsCount=0;
    stCommandsBarSettings->stStatusBarLocation.intColumn=0;
    intConsoleColumnsCount--;
    saveCursorPosition();
    if (blnStatusBar) {
        intConsoleRowsCount--;
        stCommandsBarSettings->stStatusBarLocation.intRow=intConsoleRowsCount;
        setCursorPosition(intConsoleRowsCount,0);
        printf("%*s",intConsoleColumnsCount,"");
        intConsoleRowsCount--;
        setCursorPosition(intConsoleRowsCount,0);
        printRepeatString(intConsoleColumnsCount+1,"%c",HORIZONTAL_SINGLE_BORDER);
    }
    else {
        stCommandsBarSettings->stStatusBarLocation.intRow=-1;
    }
    if (chCommandsCount) {
        chCommandsCount=ROUND(((double) chCommandsCount)/2);
        stCommandsBarSettings->stCommandsBarLocation.intRow=intConsoleRowsCount-chCommandsCount;
        stCommandsBarSettings->stCommandsBarLocation.intColumn=0;
        clearConsoleArea(stCommandsBarSettings->stCommandsBarLocation.intRow,0,chCommandsCount,intConsoleColumnsCount);
        setCursorPosition(stCommandsBarSettings->stCommandsBarLocation.intRow-1,0);
        printRepeatString(intConsoleColumnsCount+1,"%c",HORIZONTAL_SINGLE_BORDER);
    }
    resetSavedCursorPosition();
}
