#include "elevator.h"


//Elev_io functins
void setElevatorDirection(MotorDirection dir) {
    elevio_motorDirection(dir);
    return;
}

void setButtonLamp(int floor, ButtonType button, int value);
void setFloorLamp(int floor);
void setDoorOpenLamp(int value);
void setStopButton(int value);

