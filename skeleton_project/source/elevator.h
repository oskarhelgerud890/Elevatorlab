#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "driver/elevio.h"

#define NUM_DIRECTIONS 2
#define TOT_NUM_LIGHTS 16
#define NUM_ORDER_BUTTONS 8


typedef struct
{
    int OrderArray[NUM_ORDER_BUTTONS][NUM_DIRECTIONS];
    int lightArray[TOT_NUM_LIGHTS];

    int stopButton;
    int doorOpen;
    int obstructionButton;

    int currentFloor;
    int currentDirection;
    int lastDirection;

}Elevator;

/**
 * @brief Initialiser the elevator
 * 
 * @param p_elevator 
 */
void elevatorInit(Elevator* p_elevator);

/**
* @brief Wrapper functions for
* the elevio library.
*/

/**
 * @brief Set the elevator direction
 * 
 * @param dir 
 */
void setElevatorDirection(MotorDirection dir);

/**
 * @brief Set a chosen order button lamp
 * 
 * @param floor 
 * @param button 
 * @param value 
 */
void setOrderButtonLamp(int floor, ButtonType button, int value);

/**
 * @brief Set a choosen floor lamp
 * 
 * @param floor 
 */
void setFloorLamp(int floor);

/**
 * @brief Set the DoorOpen lamp
 * 
 * @param value 
 */
void setDoorOpenLamp(int value);

/**
 * @brief Set the stop-button lamp
 * 
 * @param value 
 */
void setStopLamp(int value);

/**
 * @brief Get the value of a choosen button
 * 
 * @param floor 
 * @param button 
 * @return value of button, int
 */
int getOrderButton(int floor, ButtonType button);

/**
 * @brief Get the current floor
 * 
 * @return Current floor, int
 */
int getFloor(void);

/**
 * @brief Get the value of stop button
 * 
 * @return Stop button vlaue, int 
 */
int getStopButton(void);

/**
 * @brief Get the value of the obstructon button
 * 
 * @return Obstruction button value, int 
 */
int getObstructionButton(void);


//Button Functions
void updateOrders(Elevator *p_elevator);
void checkStopButton(void);
void checkObstructionButton(void);

int chooseDirection(Elevator p_elevator);

void clearOrders(Elevator *p_elevator);

void updateOrderArray(Elevator *p_elevator);

int 


#endif // ELEVATOR_H



