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

void clearOrders(Elevator *p_elevator)
{
    for(int i=0;i<NUM_ORDER_BUTTONS;i++){
        for(int j=0; j<NUM_DIRECTIONS; j++){
            p_elevator->orderArray[i][j]=0;
        }
    }
    return;
}

//Init-function
void elevatorInit(Elevator* p_elevator){
    
    p_elevator->currentFloor=getFloor();

    while(p_elevator->currentFloor==-1){
        setElevatorDirection(DIRN_UP);
        p_elevator->currentFloor=getFloor();
      
       // nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
   
    setElevatorDirection(DIRN_STOP);

    p_elevator->currentFloor=getFloor();
    setFloorLamp(p_elevator->currentFloor);
    printf("Current floor is %d", p_elevator->currentFloor);
    clearOrders(p_elevator);
    setStopLamp(OFF);
    setDoorOpenLamp(OFF);
    return;
}



void updateorderArray(Elevator *p_elevator){
    for(int i=0;i<NUM_ORDER_BUTTONS;i++){

        if(i<4){
            p_elevator->orderArray[i][0]=getOrderButton(i,BUTTON_CAB);
            p_elevator->orderArray[i][1]=getOrderButton(i,BUTTON_CAB);
        }
        else{
            p_elevator->orderArray[i][0]=getOrderButton(i-4,BUTTON_HALL_DOWN);
            p_elevator->orderArray[i][1]=getOrderButton(i-4, BUTTON_HALL_UP);
        }
    
    }
    return;
}

int shouldStop(Elevator *p_elevator){

    if(p_elevator->orderArray[p_elevator->currentFloor][0]==1){
        return 1;
    }
    else if(p_elevator->orderArray[p_elevator->currentFloor+4][0]==1 && p_elevator->currentDirection==DIRN_DOWN){
        return 1;
    }
    else if(p_elevator->orderArray[p_elevator->currentFloor+4][1]==1 && p_elevator->currentDirection==DIRN_UP){
        return 1;
    }
    return 0;
}

int orderUpwards(Elevator *p_elevator){
    for(int i = 0; i< NUM_ORDER_BUTTONS; i++) {
        if(p_elevator->orderArray[i][DOWN_BUTTON] == ACTIVE_ORDER) {
            return ORDER_UPWARDS;
        }
    }

    return NO_ORDERS;

}


int orderDownwards(Elevator *p_elevator){
    for(int i = 0; i< NUM_ORDER_BUTTONS; i++) {
        if(p_elevator->orderArray[i][UP_BUTTON] == ACTIVE_ORDER) {
            return ORDER_DOWNWARDS;
        }
    }
    
    return NO_ORDERS;

}



MotorDirection chooseDirection(Elevator *p_elevator) {
    updateOrderArray(p_elevator);

    if(p_elevator->currentDirection == DIRN_DOWN && orderBelow(p_elevator)){ 
        return DIRN_DOWN;
    }

    else if (p_elevator->currentDirection == DIRN_UP && orderAbove(p_elevator)) {
        return DIRN_UP;
    }

    else {
        return DIRN_STOP;
    }

}