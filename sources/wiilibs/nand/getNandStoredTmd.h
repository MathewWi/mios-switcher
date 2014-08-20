#ifndef _GETNANDSTOREDTMD_H_
#define _GETNANDSTOREDTMD_H_
#include <stddef.h>
#include <ogc/es.h>
#include <gctypes.h>
signed_blob *getNandStoredTmd(u64 intTitleId,size_t *intTmdSize);
#endif
