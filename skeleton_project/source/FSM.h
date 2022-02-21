/**
 * @brief FSM module. states,cases for each state 
 * 
 */
#ifndef FSM_H
#define FSM_H

#include "elevator.h"

/**
 * @brief Enum for the different possible states of the elevator.
 */
typedef enum{
    IDLE = 0,
    MOVING = 1,
    EMERGENCY = 2,
}State;

/**
 * @brief switch containing each case/state of the elevator
 * 
 */
void FSMSwitch(State currentState);


#endif // FSM_H
