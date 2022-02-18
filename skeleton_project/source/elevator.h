#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "elevio.h"

#define NUM_CABIN_FLOOR_BUTTONS 4
#define NUM_DIRECTIONS 2
#define TOT_NUM_LIGHTS 16
#define DOOR_OPEN 1
#define DOOR_CLOSED 0

typedef struct
{
    int panelButtonArray[N_FLOORS][NUM_DIRECTIONS];
    int cabinFloorButtonArray[N_FLOORS];
    int lightArray[TOT_NUM_LIGHTS];

    int stopButton;
    int doorOpen;
    int obstructionButton;

    int currentFloor;
    int currentDirection;
    int lastDirection;

}Elevator;

void elevatorInit(void);

//Button Functions
void updatePanelButtons(Elevator *p_elevator);
void updateCabinFloorButtons(Elevator *p_elevator);
void checkStopButton(void);
void checkObstructionButton(void);

int chooseDirection(Elevator p_elevator);


#endif // ELEVATOR_H

