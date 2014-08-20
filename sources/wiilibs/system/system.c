#include <gctypes.h>
u32 intIoctlInputBuffer[8] __attribute__((aligned(0x20)));
u32 intIoctlOutputBuffer[8] __attribute__((aligned(0x20)));
bool blnUserResetRequest=false;
