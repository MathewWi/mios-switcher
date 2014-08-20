#include <string.h>
#include "truncateString.h"
char *truncateString(const char *strOverflowString,size_t intTruncateSize,char *strText) {
size_t intOverflowStringSize,intTextSize=strlen(strText);
    if (intTextSize>intTruncateSize)  {
        intOverflowStringSize=strlen(strOverflowString);
        if (intOverflowStringSize<intTruncateSize) {
            intTruncateSize=(intTruncateSize-intOverflowStringSize);
            intTextSize=intTextSize-(intTruncateSize%2);
            intTruncateSize=intTruncateSize/2;
            strcpy(strncpy(&strText[intTruncateSize],strOverflowString,intOverflowStringSize)+intOverflowStringSize,&strText[intTextSize-intTruncateSize]);
        }
    }
    return strText;
}
