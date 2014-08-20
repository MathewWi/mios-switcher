#include <stdlib.h>
#include "readDvdDataSegment.h"
#include "isDvdReady.h"
#include "dvd.h"
char *getDvdGameTitle() {
static char varout[64] __attribute__((aligned(0x20)));
    if (isDvdReady()) {
        if (readDvdDataSegment(GAME_TITLE_OFFSET,sizeof(varout),DVD_UNENCRYPTED_READ_MODE,varout)) {
            return varout;
        }
    }
    return NULL;
}
