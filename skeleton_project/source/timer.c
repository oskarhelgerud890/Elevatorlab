#include "timer.h"

void setTimer(Timer *timer) {
    timer->clockTicksElapsed = clock();
    return;
}

int checkTimer(Timer *timer) {
    clock_t newClockTicksElapsed = clock();
    float secondsElapsed = (newClockTicksElapsed - timer->clockTicksElapsed)/CLOCKS_PER_SEC;

    if(secondsElapsed == TIME_TO_ELAPSE) {
        return TIME_IS_OUT;
    }
    
    else {
        return TIME_IS_NOT_OUT;

    }
    
}