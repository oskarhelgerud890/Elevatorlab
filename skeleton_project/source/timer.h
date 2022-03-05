#ifndef TIMER_H
#define TIMER_H

#include "time.h"


#define TIME_TO_ELAPSE 3
#define TIME_OUT 1
#define TIME_NOT_OUT 0

//time_t timer;

typedef struct
{
    time_t timer;

}Timer;



void setTimer(Timer *p_timer);

int checkTimer(double timeToElapse, Timer *p_timer);


#endif // TIMER_H

