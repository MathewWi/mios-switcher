#include "../macros.h"
#include "swapBytes.h"
unsigned char *swapBytes(unsigned char *chBytes,size_t intBytesCount) {
unsigned int intSwapsCount=intBytesCount/2;
    intBytesCount--;
    while (intSwapsCount) {
        intSwapsCount--;
        SWAP(&chBytes[intSwapsCount],&chBytes[intBytesCount-intSwapsCount]);
    }
    return chBytes;
}
