/**
* @file
* @brief Contains the FSM struct, and functions that makes the elevator take decisions, 
* such as which direction to move, and if it should stop. 
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
 * @brief keeps track of which state the elevator is in
 * @var currentState contains the current state of the elevator
 */
typedef struct
{
    State currentState;
}FSM;

/**
 * @brief switch containing each state of the elevator, and the appropriate elevator-functionality
 * @param[] p_fsm
 * @param[] p_elevator
 * @param[] p_timer
 */
void FSMSpinOnce(FSM *p_fsm, Elevator *p_elevator, Timer *p_timer);

#endif // FSM_H
