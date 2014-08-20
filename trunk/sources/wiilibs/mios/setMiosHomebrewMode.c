#include <string.h>
#include <stdlib.h>
#include <ogc/cache.h>
#include "../system/initCacheCodeSegment.h"
#include "../system/setCacheCodeSegment.h"
#include "../dol/dol.h"
#include "mios.h"
#include "setMiosHomebrewMode.h"
void setMiosHomebrewMode(const u8 *chMiosDolBooter,size_t intMiosDolBooterSize,const u8 *chGcDol,size_t intGcDolSize) {
    if (chGcDol!=NULL) {
        if ((intGcDolSize>DOL_HEADER_STRUCTURE_SIZE) && (intGcDolSize<=GC_DOL_IMAGE_MAXSIZE)) {
            memset(MIOS_MAGICWORD_ADDRESS,0,32);
            strcpy(MIOS_MAGICWORD_ADDRESS,"gchomebrew dol");
            if (chMiosDolBooter==NULL) {
                memcpy(MIOS_HOMEBREW_ADDRESS,chGcDol,intGcDolSize);
                intGcDolSize=intGcDolSize+32;
            }
            else {
                if (*((u32 *)(chGcDol+DOL_ENTRY_POINT_OFFSET))>DOL_ADDRESS_LIMIT) {
                    setCacheCodeSegment(DOL_IMAGE_LOWER_ENTRY_POINT,intGcDolSize,(void *) chGcDol);
                }
                else {
                    setCacheCodeSegment(DOL_IMAGE_ENTRY_POINT,intGcDolSize,(void *) chGcDol);
                    initCacheCodeSegment(DOL_IMAGE_LOWER_ENTRY_POINT,32,0);
                }
                memcpy(MIOS_HOMEBREW_ADDRESS,chMiosDolBooter,intMiosDolBooterSize);
                intGcDolSize=intMiosDolBooterSize+32;
            }
            DCFlushRange(MIOS_MAGICWORD_ADDRESS,intGcDolSize);
            ICInvalidateRange(MIOS_MAGICWORD_ADDRESS,intGcDolSize);
        }
	}
}

