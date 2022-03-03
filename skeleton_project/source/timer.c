#include "timer.h"

void setTimer(Timer *timer) {
    timer->clockTicksElapsed = clock();
    return;
}

int isTimeOut(Timer *timer) {
    clock_t newClockTicksElapsed = clock();
    int secondsElapsed = (newClockTicksElapsed - timer->clockTicksElapsed)*1000/CLOCKS_PER_SEC;

    if(secondsElapsed >= TIME_TO_ELAPSE) {
        return TIME_IS_OUT;
    }
    
    else {
        return TIME_IS_NOT_OUT;

    }
    
}