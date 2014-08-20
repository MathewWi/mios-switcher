#ifndef _MENU_H_
#define _MENU_H_
#include <stdbool.h>
#include "../../clibs/macros.h"
#define LIST_PAGE_ITEMS_COUNT(i,p,t) ((unsigned char) (MIN((t)-((i)*(p)),(p))))
#define LIST_TOTAL_PAGES_COUNT(p,t) ((unsigned int) (((double) (t)-1)/(p))+1)
#define LIST_PAGE_INDEX(f,p) ((unsigned int) ((f)/(p)))
#define LIST_PAGE_START_ITEM_INDEX(f,p) (LIST_PAGE_INDEX((f),(p))*(p))
struct stListItem {
    unsigned int intId;
    char *strLabel;
    void *varMetaDatas;
    bool blnMarked;
    signed char chStatus;
};
enum {
    LIST_ITEM_STRUCTURE_SIZE=sizeof(struct stListItem)
};
#endif
