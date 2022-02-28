/**
 * @brief FSM module. states,cases for each state 
 * 
 */
#ifndef FSM_H
#define FSM_H

#include "elevator.h"

#define ON 1
#define OFF 0
#define UP 1
#define DOWN -1
#define STOP 0
#define BETWEEN -1

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
void FSMSwitch(State currentState, Elevator *p_elevator);


#endif // FSM_H
