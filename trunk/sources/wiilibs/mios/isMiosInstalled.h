#ifndef _ISMIOSINSTALLED_H_
#define _ISMIOSINSTALLED_H_
#include <gctypes.h>
#include "../titles/titles.h"
bool isMiosInstalled(u8 *chMiosBootContentHash,struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount);
#endif
