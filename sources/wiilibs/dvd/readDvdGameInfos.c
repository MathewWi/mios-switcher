#include "../../clibs/libfile/readFileDataSegment.h"
#include "readDvdGameInfos2.h"
#include "readDvdGameInfos.h"
enum DVD_DISC_TYPES readDvdGameInfos(FILE *fhDisc,unsigned int intHeaderOffset,struct stDvdDiscInfos *stDiscInfos) {
unsigned int intDiscMagicWord;
    if (readFileDataSegment(fhDisc,intHeaderOffset+GC_MAGICWORD_OFFSET,4,SEEK_SET,&intDiscMagicWord)==4) {
        if (intDiscMagicWord==GC_MAGICWORD) {
            if (readDvdGameInfos2(fhDisc,intHeaderOffset,stDiscInfos)) {
                return GC_DVD_DISC;
            }
        }
        else {
            if (readFileDataSegment(fhDisc,intHeaderOffset+WII_MAGICWORD_OFFSET,4,SEEK_SET,&intDiscMagicWord)==4) {
                if (intDiscMagicWord==WII_MAGICWORD) {
                    if (readDvdGameInfos2(fhDisc,intHeaderOffset,stDiscInfos)) {
                        return WII_DVD_DISC;
                    }
                }
            }
        }
    }
    return UNKNOWN_DVD_DISC;
}
