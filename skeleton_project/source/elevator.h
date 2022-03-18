/**
* @file
* @brief Library for the elevator. Contains functions for handling orders, setting lights and accessing button values.
*/

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "driver/elevio.h"
#include "defines.h"


/** @struct Elevator
 *  @brief Keep track of variables that are important for operating the elevators behaviour in fsm. \n
 *  orderArray contains the value of all order buttons: 1 if a given button has been pressed, 0 if not. \n
 *  First 4 rows corresponds to cabin buttons, 4 last to buttons outside of cabin. \n
 *  First coloumn corresponds to down buttons, second (and last) to up buttons. \n
 *  currentObstructionValue keep track of value of obstruction button. 1 if pressed, 0 if not. \n
 *  lastObstructionValue keep track of last value of obstruction button. 1 if pressed, 0 if not. \n
 *       Used to check if obstruction button recently has changed value. \n
 *  doorOpen 1 if door is open, 0 if not. \n
 *  currentFloor keep track of which floot the elevator is in. Is set to the floor the elevator last was in, if elevator is between floors. \n
 *  currentDirection keep track of which direction the elevator is moving; up/down/still. \n
 *  lastDirection keep track of which direction the elevator last was moving; up/down/still. \n
 *       Used for state transitions and deciding next moving direction in fsm. \n
 */
typedef struct
{
    int orderArray[NUM_ORDER_BUTTONS][NUM_DIRECTIONS];
    int currentObstructionValue;
    int lastObstructionValue;
    int doorOpen;
    int currentFloor;
    MotorDirection currentDirection;
    MotorDirection lastDirection;

}Elevator;

/**
 * @brief Initializer for the elevator. \n
 * Elevator moves until a floor is reached. Variables are set so that the state of the elevator is known.
 * @param[in, out] p_elevator 
 */
void elevatorInit(Elevator* p_elevator);


//Functions down to, and including, getObstructionButton() are Wrapper functions for elevio.

/**
 * @brief Set the elevator motor direction
 * 
 * @param[in] dir 
 */
void setElevatorDirection(MotorDirection dir);


/**
 * @brief Set a chosen order button lamp
 * 
 * @param[in] floor 
 * @param[in] button 
 * @param[in] value 
 */
void setOrderButtonLamp(int floor, ButtonType button, int value);


/**
 * @brief Set a chosen floor lamp
 * 
 * @param[in] floor 
 */
void setFloorLamp(int floor);


/**
 * @brief Set the doorOpen lamp
 * 
 * @param[in] value 
 */
void setDoorOpenLamp(int value);


/**
 * @brief Set the stop-button lamp
 * 
 * @param[in] value 
 */
void setStopLamp(int value);


/**
 * @brief get the value corresponding which floor the elevator is in.
 * @return number of the floor the elevator is in. -1 if elevator is between floors. \n
 * Floors are zero indexed, meaning floor 1 has the value 0. 
 */
int getFloor(void);


/**
 * @brief Get the value of stop button
 * @return 1 if button is pressed, 0 if not.
 */
int getStopButton(void);


/**
 * @brief Get the value of the obstructon button
 * @return 1 if button is pressed, 0 if not.
 */
int getObstructionButton(void);


/**
 * @brief Clear all orders of the elevator by setting all elements of the order array to 0.
 * @param[in, out] p_elevator 
 */
void clearOrders(Elevator *p_elevator);


/**
 * @brief Update orders by checking if the order buttons have been pressed. If so, the corresponding element in the order array gets the value 1.
 * @param[in, out] p_elevator  
 */
void updateOrderArray(Elevator *p_elevator);


/**
 * @brief Update order lights by checking elements in orderArray.
 * @param[in, out] p_elevator  
 */
void updateOrderLights(Elevator *p_elevator);


/**
 * @brief Decide if the elevator should stop by checking if an order on the current floor fulfills a set of requirements.
 * @param[in] p_elevator 
 * @return 0 if there are any relevant orders and 1 if not.
 */
int shouldStop(Elevator *p_elevator);


/**
 * @brief Check if there are any orders on the floors above the current floor of the elevator.
 * @param[in] p_elevator 
 * @return 1 if there is any and 0 if not.
 */
int orderAbove(Elevator *p_elevator);


/**
 * @brief Check if there are any orders below the current floor of the elevator.
 * @param[in] p_elevator 
 * @return 1 if there is any and 0 if not.
 */
int orderBelow(Elevator *p_elevator);


/**
 * @brief Check if there are any orders on the same floor as the elevator.
 * @param[in] p_elevator 
 * @return 1 if there is any and 0 if not.
 */
int orderOnCurrentFloor(Elevator *p_elevator);


/**
 * @brief Choose which direction the elevator should move based on where there are active orders relative to physical posisiton of the elevator
 * @param[in] p_elevator
 * @return -1 if downwards, 1 if upwards, 0 if elevator should stand still
 */
MotorDirection chooseDirection(Elevator *p_elevator);

/**
 * @brief Clear order(s) on the floor if the elevator stops, hence executing the order(s).
 * @param[in, out] p_elevator 
 */
void clearOrdersOnFloor(Elevator *p_elevator);

/**
 * @brief Print elements in order array. Tool for checking orders when testing, is not used in the program.
 * @param[in] p_elevator 
 */
void printArray(Elevator *p_elevator);

#endif // ELEVATOR_H



