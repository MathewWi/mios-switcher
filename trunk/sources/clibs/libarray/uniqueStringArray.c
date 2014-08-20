#include "../libmemory/permutePointers.h"
#include "../clibs.h"
#include "isInStringArray.h"
//version finale
unsigned int uniqueStringArray(char **strArray,unsigned int intArraySize) {
unsigned int varout=0;
    while (varout<intArraySize) {
        if (isInStringArray(strArray[varout],(const char **) &strArray[varout+1],intArraySize-varout-1)) {
            intArraySize--;
            permutePointers((void **) &strArray[varout],(void **) &strArray[intArraySize]);
        }
        else {
            varout++;
        }
    }
    return varout;
}
