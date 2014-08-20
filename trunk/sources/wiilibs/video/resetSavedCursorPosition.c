#include "setCursorPosition.h"
//version finale
extern unsigned char CONSOLE_CURSOR_CURRENT_ROW;
extern unsigned char CONSOLE_CURSOR_CURRENT_COLUMN;
void resetSavedCursorPosition() {
    setCursorPosition(CONSOLE_CURSOR_CURRENT_ROW,CONSOLE_CURSOR_CURRENT_COLUMN);
}
