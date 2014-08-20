#include "getCursorPositions.h"
//version finale
int getConsoleRow() {
int intConsoleColumn,intConsoleRow;
    getCursorPositions(&intConsoleColumn,&intConsoleRow);
    return intConsoleRow;
}
