#include <string.h>
#include <stdlib.h>
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "../../clibs/macros.h"
void *getTileTexture(const void *imgRGBAData,unsigned int intWidth,unsigned int intHeight,unsigned int intTileLeft,unsigned int intTileTop,unsigned int *intTileWidth,unsigned int *intTileHeight) {
void *varout=NULL;
    if ((intTileLeft<intWidth) && (intTileTop<intHeight)) {
        if ((!intTileLeft) && (!intTileTop) && (*intTileWidth==intWidth) && (*intTileHeight==intHeight)) {
            varout=(void *) imgRGBAData;
        }
        else {
            intHeight=intHeight-intTileTop;
            *intTileHeight=MIN(*intTileHeight,intHeight);
            intHeight=intWidth-intTileLeft;
            *intTileWidth=MIN(*intTileWidth,intHeight);
            if ((varout=getDynamicMemory(*intTileHeight*4*(*intTileWidth)))!=NULL) {
                for (intHeight=0;intHeight<*intTileHeight;intHeight++) {
                    memcpy(varout+(*intTileWidth*intHeight*4),imgRGBAData+((intTileTop+intHeight)*intWidth+intTileLeft)*4,*intTileWidth*4);
                }
            }
        }
    }
    return varout;
}
