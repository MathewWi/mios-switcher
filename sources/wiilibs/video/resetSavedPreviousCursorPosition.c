#include "setCursorPosition.h"
#include "saveCursorPosition.h"
//version finale
extern unsigned char CONSOLE_CURSOR_PREVIOUS_ROW;
extern unsigned char CONSOLE_CURSOR_PREVIOUS_COLUMN;
void resetSavedPreviousCursorPosition() {
    setCursorPosition(CONSOLE_CURSOR_PREVIOUS_ROW,CONSOLE_CURSOR_PREVIOUS_COLUMN);
    saveCursorPosition();
}
