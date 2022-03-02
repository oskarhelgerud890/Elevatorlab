#ifndef TIMER_H
#define TIMER_H

#include "time.h"


#define TIME_TO_ELAPSE 3
#define TIME_IS_OUT 1
#define TIME_IS_NOT_OUT 0

typedef struct
{
    clock_t clockTicksElapsed;

}Timer;


void setTimer();

int checkTimer();


#endif // TIMER_H

