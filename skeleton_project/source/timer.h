#ifndef TIMER_H
#define TIMER_H

#include "time.h"


#define TIME_TO_ELAPSE 3
#define TIME_OUT 1
#define TIME_NOT_OUT 0

time_t timer;


void setTimer();

int checkTimer(double timeToElapse);


#endif // TIMER_H

