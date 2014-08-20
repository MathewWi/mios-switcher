#include "getConsoleColumn.h"
#include "getConsoleRow.h"
//version finale
extern unsigned char CONSOLE_CURSOR_PREVIOUS_ROW;
extern unsigned char CONSOLE_CURSOR_CURRENT_ROW;
extern unsigned char CONSOLE_CURSOR_PREVIOUS_COLUMN;
extern unsigned char CONSOLE_CURSOR_CURRENT_COLUMN;
void saveCursorPosition() {
    CONSOLE_CURSOR_PREVIOUS_COLUMN=CONSOLE_CURSOR_CURRENT_COLUMN;
    CONSOLE_CURSOR_PREVIOUS_ROW=CONSOLE_CURSOR_CURRENT_ROW;
    CONSOLE_CURSOR_CURRENT_COLUMN=getConsoleColumn();
    CONSOLE_CURSOR_CURRENT_ROW=getConsoleRow();
}
