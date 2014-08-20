#include "getCursorPositions.h"
//version finale
int getConsoleColumn() {
int intConsoleColumn,intConsoleRow;
    getCursorPositions(&intConsoleColumn,&intConsoleRow);
    return intConsoleColumn;
}
