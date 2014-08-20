#include "readFileDataSegment.h"
//version finale
size_t readFileDataSegment(FILE *fp,unsigned int intOffset,size_t intDataSize,int intOffsetOrigin,void *varDataBlock) {
    if (intDataSize) {
        if (fseek(fp,intOffset,intOffsetOrigin)) {
            return 0;
        }
        else {
            return fread(varDataBlock,1,intDataSize,fp);
        }
    }
    return intDataSize;
}
