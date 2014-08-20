#include <stdio.h>
#include "setCursorPosition.h"
//version finale
void setCursorPosition(u8 intRow,u8 intColumn) {
    printf("\x1b[%u;%uH",intRow,intColumn);
    fflush(stdout);
}
