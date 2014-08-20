#include <stdio.h>
#include "../gui/getTextBoxRow.h"
#include "../gui/getTextBoxColumn.h"
#include "saveCursorPosition.h"
#include "setCursorPosition.h"
#include "resetSavedCursorPosition.h"
#include "clearConsoleArea.h"
//version finale
void clearConsoleArea(u8 intRow,u8 intColumn,u8 intRowsCount,u8 intColumnsCount) {
    intRow=getTextBoxRow(intRow);
    intColumn=getTextBoxColumn(intColumn);
    saveCursorPosition();
    while (intRowsCount) {
        intRowsCount--;
        setCursorPosition(intRow+intRowsCount,intColumn);
        printf("%*s",intColumnsCount,"");
    }
    resetSavedCursorPosition();
}
