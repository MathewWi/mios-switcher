#include <stdio.h>
#include "getBgColorPattern.h"
char *getBgColorPattern(enum CONSOLE_FONT_COLORS FONT_COLOR) {
static char varout[BGCOLOR_PATTERN_SIZE+1];
    sprintf(varout,"\x1b[%um",FONT_COLOR+40);
    return varout;
}
