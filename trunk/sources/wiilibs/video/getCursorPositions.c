#include <stdio.h>
#include <ogc/consol.h>
//version finale
void getCursorPositions(int *intColumn,int *intRow) {
    fflush(stdout);
    CON_GetPosition(intColumn,intRow);
}
