#include "../video/clearConsoleArea.h"
#include "getTextBoxRow.h"
#include "getTextBoxColumn.h"
#include "initLogMonitor.h"
void initLogMonitor(u8 chRow,u8 chColumn,u8 chRowsCount,u8 chColumnsCount,bool blnClear,struct stLogMonitor *stLogMonitorSettings) {
    stLogMonitorSettings->chRow=getTextBoxRow(chRow);
    stLogMonitorSettings->chColumn=getTextBoxColumn(chColumn);
    stLogMonitorSettings->chRowsCount=stLogMonitorSettings->chRow+chRowsCount-1;
    stLogMonitorSettings->chColumnsCount=chColumnsCount;
    stLogMonitorSettings->stCurrentCursorPositions.intRow=stLogMonitorSettings->chRow-1;
    stLogMonitorSettings->stCurrentCursorPositions.intColumn=stLogMonitorSettings->chColumn;
    if (blnClear) {
        clearConsoleArea(stLogMonitorSettings->chRow,stLogMonitorSettings->chColumn,chRowsCount,chColumnsCount);
    }
}
