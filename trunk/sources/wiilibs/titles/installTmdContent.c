#include <ogc/es.h>
#include "installTmdContent.h"
//version finale
s32 installTmdContent(u64 intTitleId,u32 intTmdContentId,u8 *chContentBuffer,u32 intContentSize) {
s32 varout;
int intContentFd;
    if ((intContentFd=ES_AddContentStart(intTitleId,intTmdContentId))<0) {
        varout=intContentFd;
        //TODO
    }
    else {
        if ((varout=ES_AddContentData(intContentFd,chContentBuffer,intContentSize))<0) {
            //TODO
        }
        if ((varout=ES_AddContentFinish(intContentFd))<0) {
            //TODO
        }
    }
    return varout;
}
