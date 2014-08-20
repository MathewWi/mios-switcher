#include <unistd.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <ogc/pad.h>
#include "../../clibs/libtime/libtime.h"
#include "../../clibs/libtime/initTimer.h"
#include "../../clibs/libtime/isExpiredTimer.h"
#include "../../clibs/libarray/isInArray.h"
#include "../../clibs/clibs.h"
#include "../system/getUserResetRequestStatus.h"
#include "getMappedPadsKey.h"
#include "getPadsKeyPressed.h"
//version finale
s32 getPadsKeyPressed(s32 *intExpectedPadsKeysPressed,unsigned int intExpectedPadsKeysCount,bool blnMappedPadsKey,unsigned short int intScanPadsTime,s32 intTimeoutPadsKey) {
s32 varout=0;
struct stTimer stScanPadsTimer;
    initTimer(&stScanPadsTimer,intScanPadsTime);
    while (!varout) {
        while (!varout) {
            WPAD_ScanPads();
            if ((varout=(WPAD_ButtonsDown(WPAD_CHAN_0)|WPAD_ButtonsDown(WPAD_CHAN_1)|WPAD_ButtonsDown(WPAD_CHAN_2)|WPAD_ButtonsDown(WPAD_CHAN_3)))) {
                if ((varout=(WPAD_ButtonsHeld(WPAD_CHAN_0)|WPAD_ButtonsHeld(WPAD_CHAN_1)|WPAD_ButtonsHeld(WPAD_CHAN_2)|WPAD_ButtonsHeld(WPAD_CHAN_3)))) {
                    if (blnMappedPadsKey) {
                        varout=getMappedPadsKey(varout);
                    }
                }
            }
            else {
                PAD_ScanPads();
                if ((varout=(PAD_ButtonsDown(PAD_CHAN0)|PAD_ButtonsDown(PAD_CHAN1)|PAD_ButtonsDown(PAD_CHAN2)|PAD_ButtonsDown(PAD_CHAN3)))) {
                    varout=(PAD_ButtonsHeld(PAD_CHAN0)|PAD_ButtonsHeld(PAD_CHAN1)|PAD_ButtonsHeld(PAD_CHAN2)|PAD_ButtonsHeld(PAD_CHAN3));
                }
                usleep(20000);
            }
            if (getUserResetRequestStatus()) {
                return 0;
            }
            if (isExpiredTimer(&stScanPadsTimer)) {
                return intTimeoutPadsKey;
            }
        }
        if (intExpectedPadsKeysPressed!=NULL) {
            if (!isInArray((void *) intExpectedPadsKeysPressed,intExpectedPadsKeysCount,INT_TYPE_SIZE,(void *) &varout,false)) {
                varout=0;
            }
        }
    }
    return varout;
}
