#include "../../clibs/libarray/uniqueStringArray.h"
#include "getPadKeyLabel.h"
#include "getUnmappedPadKey.h"
#include "controllers.h"
#include "getPadsKeyLabels.h"
//version finale
unsigned char getPadsKeyLabels(s32 intMappedPadKey,char **strPadsKeyLabels) {
    strPadsKeyLabels[GAMECUBE_CONTROLLER]=getPadKeyLabel(intMappedPadKey,GAMECUBE_CONTROLLER);
    strPadsKeyLabels[WIIMOTE_CONTROLLER]=getPadKeyLabel(getUnmappedPadKey(intMappedPadKey,WIIMOTE_CONTROLLER),WIIMOTE_CONTROLLER);
    strPadsKeyLabels[CLASSIC_CONTROLLER]=getPadKeyLabel(getUnmappedPadKey(intMappedPadKey,CLASSIC_CONTROLLER),CLASSIC_CONTROLLER);
    return uniqueStringArray(strPadsKeyLabels,CONTROLLERS_COUNT);
}
