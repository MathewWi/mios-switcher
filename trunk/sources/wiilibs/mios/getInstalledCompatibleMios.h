#ifndef _GETINSTALLEDCOMPATIBLEMIOS_H_
#define _GETINSTALLEDCOMPATIBLEMIOS_H_
#include "../titles/titles.h"
#include "../filesystems/filesystems.h"
struct stTitleInfos ***getInstalledCompatibleMios(const char *strDiscID,enum STORAGE_DEVICES STORAGE_DEVICE,struct stTitleInfos **stInstalledMiosInfos,unsigned char chInstalledMiosCount,unsigned char *chInstalledCompatibleMiosCount);
#endif
