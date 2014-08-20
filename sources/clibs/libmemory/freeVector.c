#include <malloc.h>
#include <stdlib.h>
//version finale
void freeVector(void **varVector) {
    if (varVector!=NULL) {
        if (*varVector!=NULL) {
            free(*varVector);
            *varVector=NULL;
        }
    }
}
