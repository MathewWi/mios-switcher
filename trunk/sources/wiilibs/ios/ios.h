#ifndef _IOS_H_
#define _IOS_H_
#include <gctypes.h>
#define MEM_REG_BASE 0xd8b4000
#define MEM_PROT (MEM_REG_BASE+0x20a)
#define HAVE_AHBPROT (*(volatile u32*)0xcd800064==0xFFFFFFFF)
enum IOS_TYPES {
    NONE_IOS=0,
    STUB_IOS=1,
    BOOTMII_IOS=2,
    RESERVED_IOS=3,
    ACTIVE_IOS=4
};
struct stSlotInfos {
    u16 intIosRevision;
    u8 chIosType;
    u8 chTmdContentIdentificationHash[20];
};
enum {
    SLOT_INFOS_STRUCTURE_SIZE=sizeof(struct stSlotInfos)
};
#endif
