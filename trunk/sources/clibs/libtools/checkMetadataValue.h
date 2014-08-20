#ifndef _CHECKMETADATAVALUE_H_
#define _CHECKMETADATAVALUE_H_
#include <stdbool.h>
#include "libtools.h"
enum METADATA_CHECKING_STATUS checkMetadataValue(const char *strMetadatasEnumeration,char chMetadatasDelimiter,char chMetadataAssignater,char chMetadataValuesDelimiter,const char *strMetadataLabel,const char *strMetadataValue);
#endif
