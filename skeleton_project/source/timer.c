#include "timer.h"
#include "defines.h"

void setTimer(Timer *p_timer) {

    p_timer->timer=time(NULL);
    return;
}

int checkTimer(double timeToElapse, Timer *p_timer) {
    double timeElapsed = difftime(time(NULL), p_timer->timer);
    if(timeElapsed >= timeToElapse) {
        return TIME_OUT;
    }
    return TIME_NOT_OUT;
}
