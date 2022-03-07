#ifndef TIMER_H
#define TIMER_H

#include "time.h"




//time_t timer;

typedef struct
{
    time_t timer;

}Timer;



void setTimer(Timer *p_timer);

int checkTimer(double timeToElapse, Timer *p_timer);


#endif // TIMER_H

