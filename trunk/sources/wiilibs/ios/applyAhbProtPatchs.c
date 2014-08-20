#include <ogc/machine/processor.h>
#include <gctypes.h>
#include "ios.h"
#include "applyOnTheFlyIosPatchs.h"
//version finale
unsigned int applyAhbProtPatchs() {
static const u8 chDiReadlimitOriginalBytes[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x40,0x00,0x00,0x00,0x00,0x00,0x46,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x7E,0xD4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08};
static const u8 chDiReadlimitNewBytes[]={0x7e,0xd4};
static const u8 chIsfsPermissionsOriginalBytes[]={0x42,0x8B,0xD0,0x01,0x25,0x66};
static const u8 chIsfsPermissionsNewBytes[]={0x42,0x8B,0xE0,0x01,0x25,0x66};
static const u8 chEsSetuidOriginalBytes[]={0xD1,0x2A,0x1C,0x39};
static const u8 chEsSetuidNewBytes[]={0x46,0xC0};
static const u8 chEsIdentifyOriginalBytes[]={0x28,0x03,0xD1,0x23};
static const u8 chEsIdentifyNewBytes[]={0x00,0x00};
static const u8 chOldTruchaOriginalBytes[]={0x20,0x07,0x23,0xA2};
static const u8 chTruchaNewBytes[]={0x00};
static const u8 chNewTruchaOriginalBytes[]={0x20,0x07,0x4B,0x0B};
static const u8 chEsVersionOriginalBytes[]={0xD2,0x01,0x4E,0x56};
static const u8 chEsVersionNewBytes[]={0xE0};
unsigned int varout=0;
    if (HAVE_AHBPROT) {
        write32(MEM_PROT,read32(MEM_PROT) & 0x0000FFFF);
        varout=varout+applyOnTheFlyIosPatchs((u8*)0x93400000,(u8*)0x94000000,chDiReadlimitOriginalBytes,sizeof(chDiReadlimitOriginalBytes),chDiReadlimitNewBytes,sizeof(chDiReadlimitNewBytes),12);
        varout=varout+applyOnTheFlyIosPatchs((u8*)0x93400000,(u8*)0x94000000,chIsfsPermissionsOriginalBytes,sizeof(chIsfsPermissionsOriginalBytes),chIsfsPermissionsNewBytes,sizeof(chIsfsPermissionsNewBytes),0);
        varout=varout+applyOnTheFlyIosPatchs((u8*)0x93400000,(u8*)0x94000000,chEsSetuidOriginalBytes,sizeof(chEsSetuidOriginalBytes),chEsSetuidNewBytes,sizeof(chEsSetuidNewBytes),0);
        varout=varout+applyOnTheFlyIosPatchs((u8*)0x93400000,(u8*)0x94000000,chEsIdentifyOriginalBytes,sizeof(chEsIdentifyOriginalBytes),chEsIdentifyNewBytes,sizeof(chEsIdentifyNewBytes),2);
        varout=varout+applyOnTheFlyIosPatchs((u8*)0x93400000,(u8*)0x94000000,chOldTruchaOriginalBytes,sizeof(chOldTruchaOriginalBytes),chTruchaNewBytes,sizeof(chTruchaNewBytes),1);
        varout=varout+applyOnTheFlyIosPatchs((u8*)0x93400000,(u8*)0x94000000,chNewTruchaOriginalBytes,sizeof(chNewTruchaOriginalBytes),chTruchaNewBytes,sizeof(chTruchaNewBytes),1);
        varout=varout+applyOnTheFlyIosPatchs((u8*)0x93400000,(u8*)0x94000000,chEsVersionOriginalBytes,sizeof(chEsVersionOriginalBytes),chEsVersionNewBytes,sizeof(chEsVersionNewBytes),0);
    }
    return varout;
}
