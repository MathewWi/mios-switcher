#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
//version finale
unsigned int printJoinedArrayStringMemoryItems(const char **strMemoryItems,unsigned int *intMemoryItemsIndexes,unsigned int intMemoryItemsCount,unsigned int intMemoryStepSize,const char *strBeforeItem,const char *strSeparator,const char *strAfterItem,const char *strJoin) {
unsigned int varout=0,i;
unsigned char chMultiplicateur=(*strSeparator)?1:0;
    if (intMemoryItemsIndexes==NULL) {
        varout=printf("%s%.*u%s%s%s",strBeforeItem,chMultiplicateur,0,strSeparator,*((char **) ((char *) strMemoryItems)),strAfterItem);
        for (i=1;i<intMemoryItemsCount;i++) {
            varout=varout+printf("%s%s%.*u%s%s%s",strJoin,strBeforeItem,chMultiplicateur,i*chMultiplicateur,strSeparator,*((char **) ((char *) strMemoryItems+i*intMemoryStepSize)),strAfterItem);
        }
    }
    else {
        varout=printf("%s%.*u%s%s%s",strBeforeItem,chMultiplicateur,intMemoryItemsIndexes[0]*chMultiplicateur,strSeparator,*((char **) ((char *) strMemoryItems+intMemoryItemsIndexes[0]*intMemoryStepSize)),strAfterItem);
        for (i=1;i<intMemoryItemsCount;i++) {
            varout=varout+printf("%s%s%.*u%s%s%s",strJoin,strBeforeItem,chMultiplicateur,intMemoryItemsIndexes[i]*chMultiplicateur,strSeparator,*((char **) ((char *) strMemoryItems+intMemoryItemsIndexes[i]*intMemoryStepSize)),strAfterItem);
        }
    }
    return varout;
}
