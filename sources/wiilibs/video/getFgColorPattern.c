#include <stdio.h>
#include "getFgColorPattern.h"
char *getFgColorPattern(enum CONSOLE_FONT_COLORS FONT_COLOR,enum CONSOLE_FONT_WEIGHTS FONT_WEIGHT) {
static char varout[FGCOLOR_PATTERN_SIZE+1];
    sprintf(varout,"\x1b[%u;%um",FONT_COLOR+30,FONT_WEIGHT);
    return varout;
}
