#include "timer.h"

void setTimer() {

    timer=time(NULL);
    return;
}

int checkTimer(double timeToElapse) {
    double timeElapsed = difftime(time(NULL), timer);
    if(timeElapsed >= timeToElapse) {
        return TIME_OUT;
    }
    return TIME_NOT_OUT;
}
