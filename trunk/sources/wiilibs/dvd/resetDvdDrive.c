#include "initDvd.h"
#include "resetDvd.h"
#include "stopDvd.h"
void resetDvdDrive() {
    if (initDvd()) {
        resetDvd();
        stopDvd();
    }
}
