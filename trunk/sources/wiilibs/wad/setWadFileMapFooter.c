#include <stdlib.h>
#if defined(_WIN64) || defined(_WIN32)
#include "../../clibs/libtools/swapBytes.h"
#endif
#include "../../clibs/libmemory/getDynamicMemory.h"
#include "../../clibs/macros.h"
#include "setWadFileMapFooter.h"
//version finale
bool setWadFileMapFooter(signed_blob *sTmd,struct stWadHeader *stWadTitleHeader,struct stWadMap *stWadFileMap) {
tmd *pTmd;
#if defined(_WIN64) || defined(_WIN32)
u64 intTempVar;
#endif
    if (IS_VALID_SIGNATURE(sTmd)) {
        if ((pTmd=SIGNATURE_PAYLOAD(sTmd))!=(tmd *) sTmd) {
            stWadFileMap->intTmdContentsCount=pTmd->num_contents;
#if defined(_WIN64) || defined(_WIN32)
            swapBytes((unsigned char *) &stWadFileMap->intTmdContentsCount,sizeof(stWadFileMap->intTmdContentsCount));
#endif
            if ((stWadFileMap->stTmdContents=getDynamicMemory(stWadFileMap->intTmdContentsCount*WAD_CONTENT_STRUCTURE_SIZE))!=NULL) {
                stWadFileMap->intOffsetFooterData=stWadFileMap->intOffsetTmdData+ROUND_UP(stWadFileMap->intTmdDataSize,64);
                for (stWadFileMap->intFooterDataSize=0;stWadFileMap->intFooterDataSize<stWadFileMap->intTmdContentsCount;stWadFileMap->intFooterDataSize++) {
                    stWadFileMap->stTmdContents[stWadFileMap->intFooterDataSize].intOffsetContentData=stWadFileMap->intOffsetFooterData;
#if defined(_WIN64) || defined(_WIN32)
                    intTempVar=pTmd->contents[stWadFileMap->intFooterDataSize].size;
                    stWadFileMap->stTmdContents[stWadFileMap->intFooterDataSize].intContentDataSize=ROUND_UP(*((size_t *) swapBytes((unsigned char *) &intTempVar,sizeof(intTempVar))),16);
#else
                    stWadFileMap->stTmdContents[stWadFileMap->intFooterDataSize].intContentDataSize=ROUND_UP(pTmd->contents[stWadFileMap->intFooterDataSize].size,16);
#endif
                    stWadFileMap->intOffsetFooterData=stWadFileMap->intOffsetFooterData+ROUND_UP(stWadFileMap->stTmdContents[stWadFileMap->intFooterDataSize].intContentDataSize,64);
                }
                stWadFileMap->intFooterDataSize=stWadTitleHeader->intFooterSize;
#if defined(_WIN64) || defined(_WIN32)
                stWadFileMap->intFooterDataSize=*((size_t *) swapBytes((unsigned char *) &stWadFileMap->intFooterDataSize,sizeof(stWadFileMap->intFooterDataSize)));
#endif
                return true;
            }
        }
    }
    return false;
}
