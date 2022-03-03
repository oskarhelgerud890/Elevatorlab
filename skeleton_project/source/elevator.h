#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "driver/elevio.h"

#define NUM_DIRECTIONS 2
#define TOT_NUM_LIGHTS 16
#define NUM_ORDER_BUTTONS 8
#define ON 1
#define OFF 0
#define UP 1
#define DOWN -1
#define STOP 0
#define BETWEEN -1
#define NUM_FLOORS 4

#define ORDER_UP_ABOVE 1
#define ORDER_UP_BELOW 2
#define ORDER_DOWN_ABOVE 3
#define ORDER_DOWN_BELOW 4

#define ORDER_UPWARDS 1
#define ORDER_DOWNWARDS 1
#define ACTIVE_ORDER 1
#define NO_ORDERS 0
#define DOWN_BUTTON 0
#define UP_BUTTON 1


typedef struct
{
    int orderArray[NUM_ORDER_BUTTONS][NUM_DIRECTIONS];

    int stopButton;
    int doorOpen;
    int obstructionButton;

    int currentFloor;
    MotorDirection currentDirection;
    MotorDirection lastDirection;


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

/**void checkStopButton(void);rief Get the current floor
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
void checkObstructionButton(void);

void clearOrders(Elevator *p_elevator);

void updateOrderArray(Elevator *p_elevator);

void updateOrderLights(Elevator *p_elevator);

int shouldStop(Elevator *p_elevator);


// choose direction stuff
int shouldStop(Elevator *p_elevator);
int orderUpwards(Elevator *p_elevator);
int orderDownwards(Elevator *p_elevator);
MotorDirection chooseDirection(Elevator *p_elevator);

void printArray(Elevator *p_elevator);


#endif // ELEVATOR_H



