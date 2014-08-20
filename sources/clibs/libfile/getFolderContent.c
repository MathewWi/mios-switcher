#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/dirent.h>
#include "../libarray/insertArrayItems.h"
#include "../libmemory/freeVector.h"
#include "../libmemory/freeRecursiveVector.h"
#include "../libmemory/reallocBuffer.h"
#include "../clibs.h"
#include "isDirectory.h"
#include "getFolderContent.h"
char **getFolderContent(const char *strFolderPath,bool blnRecursive,unsigned int *intDirectoryItemsCount) {
char **varout=NULL,**strFolderItems=NULL,strDirectoryItemPath[256];
DIR *stDirectory;
struct dirent *stDirectoryItem;
unsigned int intFolderItemsCount;
unsigned char chAddSlashChar;
    *intDirectoryItemsCount=0;
    if ((stDirectory=opendir(strFolderPath))!=NULL) {
        chAddSlashChar=strFolderPath[strlen(strFolderPath)-1]-'/';
		while ((stDirectoryItem=readdir(stDirectory))) {
		    if ((strcmp(stDirectoryItem->d_name,".")) && (strcmp(stDirectoryItem->d_name,".."))) {
                if (reallocBuffer((void **) &varout,(*intDirectoryItemsCount+1)*POINTER_TYPE_SIZE,0)==NULL) {
                    freeRecursiveVector((void ***) &varout,*intDirectoryItemsCount);
                    *intDirectoryItemsCount=0;
                    break;
                }
                else {
                    snprintf(strDirectoryItemPath,sizeof(strDirectoryItemPath),"%s%.*s%s",strFolderPath,chAddSlashChar,"/",stDirectoryItem->d_name);
                    varout[*intDirectoryItemsCount]=strdup(strDirectoryItemPath);
                    *intDirectoryItemsCount=*intDirectoryItemsCount+1;
                    if (blnRecursive) {
                        if (isDirectory(strDirectoryItemPath)) {
                            if ((strFolderItems=getFolderContent(strDirectoryItemPath,blnRecursive,&intFolderItemsCount))!=NULL) {
                                if (insertArrayItems((void **) &varout,intDirectoryItemsCount,*intDirectoryItemsCount,POINTER_TYPE_SIZE,-1*intFolderItemsCount,strFolderItems)>*intDirectoryItemsCount) {
                                    freeRecursiveVector((void ***) &strFolderItems,intFolderItemsCount);
                                    freeRecursiveVector((void ***) &varout,*intDirectoryItemsCount);
                                    *intDirectoryItemsCount=0;
                                    break;
                                }
                                else {
                                    freeVector((void **) &strFolderItems);
                                }
                            }
                        }
                    }
                }
            }
        }
        closedir(stDirectory);
	}
	return varout;
}
