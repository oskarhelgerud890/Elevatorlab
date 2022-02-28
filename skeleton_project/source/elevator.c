#include "elevator.h"
#include <stdio.h>
#include <time.h>
#include "driver/elevio.h"




//Elev_io functins
void setElevatorDirection(MotorDirection dir) {
    elevio_motorDirection(dir);
    return;
}

void setOrderButtonLamp(int floor, ButtonType button, int value){
    elevio_buttonLamp(floor, button, value);
    return;
}

void setFloorLamp(int floor){
    elevio_floorIndicator(floor);
    return;
}

void setDoorOpenLamp(int value){
    elevio_doorOpenLamp(value);
    return;
}

void setStopLamp(int value){
    elevio_stopLamp(value);
    return;
}

int getOrderButton(int floor, ButtonType button){
    return elevio_callButton(floor, button);  
}

int getFloor(void){
    return elevio_floorSensor();
}

int getStopButton(void){
    return elevio_stopButton();
}

int getObstructionButton(void){
    return elevio_obstruction();
}

//Init-function
void elevatorInit(Elevator* p_elevator){
    
    p_elevator->currentFloor=getFloor();

    while(p_elevator->currentFloor==-1){
        setElevatorDirection(DIRN_UP);
        p_elevator->currentFloor=getFloor();
      
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
   
    setElevatorDirection(DIRN_STOP);

    p_elevator->currentFloor=getFloor();
    setFloorLamp(p_elevator->currentFloor);
    printf("Current floor is %d", p_elevator->currentFloor);
    return;
}

void clearOrders(Elevator *p_elevator)
{
    for(int i=0;i<NUM_ORDER_BUTTONS;i++){
        for(int j=0; j<NUM_DIRECTIONS; j++){
            p_elevator->OrderArray[i][j]=0;
        }
    }
    return;
}