#include <stdio.h>
#include <string.h>
#include "printTruncatedText.h"
int printTruncatedText(const char *strOverflowString,size_t intTruncateSize,const char *strText) {
size_t intOverflowStringSize,intTextSize=strlen(strText);
    if (intTextSize>intTruncateSize)  {
        intOverflowStringSize=strlen(strOverflowString);
        if (intOverflowStringSize<intTruncateSize) {
            printf("%s",&strText[intTextSize-intTruncateSize+printf("%.*s%s",(intTruncateSize-intOverflowStringSize)/2,strText,strOverflowString)]);
            return intTruncateSize;
        }
    }
    else {
        return printf("%s",strText);
    }
    return 0;
}
