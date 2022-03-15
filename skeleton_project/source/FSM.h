/**
* @file
* @brief Interface for ...
*/

#ifndef FSM_H
#define FSM_H

#include "elevator.h"
#include "timer.h"

/**
 * @brief Enum for the different possible states of the elevator.
 */

typedef enum{
    IDLE = 0,
    MOVING = 1,
    EMERGENCY = 2,
}State;

typedef struct
{
    //Elevator *p_elevator;
    State currentState;
    //Timer *p_timer;
}FSM;

/**
 * @brief switch containing each case/state of the elevator
 * 
 */
void FSMSpinOnce(FSM *p_fsm, Elevator *p_elevator, Timer *p_timer);


#endif // FSM_H
