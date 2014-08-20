#include <string.h>
#include <stdlib.h>
#include "../libstring/getSplitStrings.h"
#include "../libmemory/freeRecursiveVector.h"
#include "checkMetadataValue.h"
enum METADATA_CHECKING_STATUS checkMetadataValue(const char *strMetadatasString,char chMetadatasDelimiter,char chMetadataAssignater,char chMetadataValuesDelimiter,const char *strMetadataLabel,const char *strMetadataValue) {
char *strLabel,**strMetadatas=NULL;
unsigned int intMetadatasCount=1;
static char strMetadatasDelimiter[2]={0,0};
enum METADATA_CHECKING_STATUS varout=MISSING_METADATA_STATUS;
    if (strMetadatasString!=NULL) {
        if ((strLabel=strstr(strMetadatasString,strMetadataLabel))!=NULL) {
            if ((strLabel==strMetadatasString) || (*(strLabel-1)==chMetadatasDelimiter)) {
                varout=NOTFOUND_METADATA_STATUS;
                strLabel=strLabel+strlen(strMetadataLabel);
                if (*strLabel==chMetadataAssignater) {
                    if (chMetadataValuesDelimiter) {
                        strMetadatasDelimiter[0]=chMetadatasDelimiter;
                        if ((strMetadatas=getSplitStrings(strLabel+1,strMetadatasDelimiter,&intMetadatasCount))!=NULL) {
                            if ((strLabel=strstr(strMetadatas[0],strMetadataValue))!=NULL) {
                                if ((strLabel==strMetadatas[0]) || (*(strLabel-1)==chMetadataValuesDelimiter)) {
                                    strLabel=strLabel+strlen(strMetadataValue);
                                    if ((*strLabel==0) || (*strLabel==chMetadataValuesDelimiter)) {
                                        varout=MATCHING_METADATA_STATUS;
                                    }
                                }
                            }
                            freeRecursiveVector((void ***) &strMetadatas,intMetadatasCount);
                        }
                    }
                    else {
                        strLabel=strLabel+1;
                        if (!strncmp(strLabel,strMetadataValue,strlen(strMetadataValue))) {
                            strLabel=strLabel+strlen(strMetadataValue);
                            if ((*strLabel==0) || (*strLabel==chMetadatasDelimiter)) {
                                varout=MATCHING_METADATA_STATUS;
                            }
                        }
                    }
                }
            }
        }
    }
    return varout;
}
