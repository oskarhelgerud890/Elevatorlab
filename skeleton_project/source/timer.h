/**
* @file
* @brief contains the functions related to the timer
*/

#ifndef TIMER_H
#define TIMER_H

#include "time.h"

/** @struct Timer
 * @brief contains a timer variable that keeps track of when the timer started
 * @var timer
 */ 
typedef struct
{
    time_t timer;
}Timer;

/**
 * @brief starts the timer by setting the variable in the Timer struct
 * @param[] p_timer
 */
void setTimer(Timer *p_timer);

/**
 * @brief Checks if the timer has been on for more than three seconds
 * @param[] timeToElapse
 * @param[] p_timer
 */
int checkTimer(double timeToElapse, Timer *p_timer);

#endif // TIMER_H

