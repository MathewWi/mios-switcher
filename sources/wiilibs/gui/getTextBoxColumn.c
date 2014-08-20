#include "../video/getConsoleColumn.h"
#include "gui.h"
#include "getTextBoxColumn.h"
//version finale
u8 getTextBoxColumn(u8 chColumn) {
    return (chColumn==AUTOSIZE)?getConsoleColumn():chColumn;
}
