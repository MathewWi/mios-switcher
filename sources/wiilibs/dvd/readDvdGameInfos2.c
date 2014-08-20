#include "../../clibs/libfile/readFileDataSegment.h"
#include "readDvdGameInfos2.h"
bool readDvdGameInfos2(FILE *fhDisc,unsigned int intHeaderOffset,struct stDvdDiscInfos *stDiscInfos) {
    if (readFileDataSegment(fhDisc,intHeaderOffset,10,SEEK_SET,stDiscInfos->strDiscID)==10) {
        return (readFileDataSegment(fhDisc,intHeaderOffset+GAME_TITLE_OFFSET,64,SEEK_SET,stDiscInfos->strGameTitle)==64);
    }
    return false;
}
