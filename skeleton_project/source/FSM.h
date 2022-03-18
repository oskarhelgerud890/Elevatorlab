/**
* @file
* @brief Interface for the finite state maschine, which is used for decision-making.
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


/** @struct FSM
 * @brief keeps track of which state the elevator currently is in \n
 * currentState contains the current state of the elevator
 */
typedef struct
{
    State currentState;
}FSM;

/**
 * @brief Switch-function containing each state of the elevator as cases, and the appropriate elevator-functionality
 * @param[in, out] p_fsm
 * @param[in, out] p_elevator
 * @param[in, out] p_timer
 */
void FSMSpinOnce(FSM *p_fsm, Elevator *p_elevator, Timer *p_timer);

#endif // FSM_H
