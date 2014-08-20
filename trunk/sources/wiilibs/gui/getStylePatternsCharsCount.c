#include <string.h>
#include "../video/video.h"
#include "getStylePatternsCharsCount.h"
size_t getStylePatternsCharsCount(const char *strText) {
size_t varout=0;
char *strStylePattern=(char *) strText-FGCOLOR_PATTERN_SIZE;
    while ((strStylePattern=strstr(strStylePattern+FGCOLOR_PATTERN_SIZE,FGCOLOR_PATTERN_PREFIX))!=NULL) {
        varout=varout+FGCOLOR_PATTERN_SIZE;
    }
    strStylePattern=(char *) strText-BGCOLOR_PATTERN_SIZE;
    while ((strStylePattern=strstr(strStylePattern+BGCOLOR_PATTERN_SIZE,BGCOLOR_PATTERN_PREFIX))!=NULL) {
        varout=varout+BGCOLOR_PATTERN_SIZE;
    }
    return varout;
}
