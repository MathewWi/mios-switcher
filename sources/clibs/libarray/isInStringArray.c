#include <string.h>
#include "isInStringArray.h"
//version finale
bool isInStringArray(const char *strValue,const char **strArray,unsigned int intArraySize) {
bool varout=false;
    while ((intArraySize) && (!varout)) {
        intArraySize--;
        varout=(strcmp(strValue,strArray[intArraySize])==0);
    }
    return varout;
}
