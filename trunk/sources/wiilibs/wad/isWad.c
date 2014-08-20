#include <string.h>
#include "isWad.h"
//version finale
bool isWad(void *chWadBuffer) {
static unsigned char chWadFormatBytes[6]={0x0,0x0,0x0,0x20,0x49,0x73};
    return (memcmp(chWadBuffer,chWadFormatBytes,sizeof(chWadFormatBytes))==0);
}
