#include "../video/getConsoleRow.h"
#include "gui.h"
#include "getTextBoxRow.h"
//version finale
u8 getTextBoxRow(u8 chRow) {
    return (chRow==AUTOSIZE)?getConsoleRow():chRow;
}
