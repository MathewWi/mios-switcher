#include <unistd.h>
#include <ogc/machine/processor.h>
#include <ogc/ios.h>
#include <gctypes.h>
#include "ios.h"
#include "applyOnTheFlyIosPatchs.h"
//version finale
unsigned int setAhbProtAccessRights() {
static const u8 chAhbprotOriginalBytes[]={0x68,0x5B,0x22,0xEC,0x00,0x52,0x18,0x9B,0x68,0x1B,0x46,0x98,0x07,0xDB};
static const u8 chAhbprotNewBytes[]={0x01};
unsigned int varout=0;
    if (HAVE_AHBPROT) {
        write32(MEM_PROT,read32(MEM_PROT) & 0x0000FFFF);
        varout=applyOnTheFlyIosPatchs((u8*)*((u32*)0x80003134),(u8*)0x94000000,chAhbprotOriginalBytes,sizeof(chAhbprotOriginalBytes),chAhbprotNewBytes,sizeof(chAhbprotNewBytes),25);
        IOS_ReloadIOS(IOS_GetVersion());
        sleep(1);
    }
    return varout;
}
