#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "elevio.h"

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

void elevatorInit(void);

/**
* @brief Set elevator direction. Wrapper function for
* the elevio library.
*/


//Elev_io functins
void setElevatorDirection(MotorDirection dir);
void setButtonLamp(int floor, ButtonType button, int value);
void setFloorLamp(int floor);
void setDoorOpenLamp(int value);
void setStopButton(int value);

//Button Functions
void updateOrders(Elevator *p_elevator);
void checkStopButton(void);
void checkObstructionButton(void);

int chooseDirection(Elevator p_elevator);


#endif // ELEVATOR_H



