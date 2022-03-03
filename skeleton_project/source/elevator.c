#include "elevator.h"
#include <stdio.h>
#include <time.h>
#include "driver/elevio.h"




// wrapper-functions for Elev_io functins
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
void elevatorInit(Elevator *p_elevator){
    
    p_elevator->currentFloor=getFloor();

    while(p_elevator->currentFloor==-1){
        setElevatorDirection(DIRN_UP);
        p_elevator->currentFloor=getFloor();
      
       // nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
   
    setElevatorDirection(DIRN_STOP);

   // printf("Current floor is %d", p_elevator->currentFloor);
    setFloorLamp(p_elevator->currentFloor);
    setStopLamp(OFF);
    setDoorOpenLamp(OFF);
    clearOrders(p_elevator);
    updateOrderLights(p_elevator);
    p_elevator->currentDirection=DIRN_STOP;

    return;
}



void updateOrderArray(Elevator *p_elevator){
    for(int buttonIndex = 0; buttonIndex < NUM_ORDER_BUTTONS; buttonIndex++){

        if(buttonIndex<4){
        
            int isOrderCabin = getOrderButton(buttonIndex, BUTTON_CAB);

            if(isOrderCabin==ON && p_elevator->orderArray[buttonIndex][DOWN_BUTTON]==OFF){
                p_elevator->orderArray[buttonIndex][DOWN_BUTTON] = ON;
                p_elevator->orderArray[buttonIndex][UP_BUTTON] = ON;
            }


        }
        else{
            int isOrderDown = getOrderButton(buttonIndex-4,BUTTON_HALL_DOWN);
            int isOrderUp = getOrderButton(buttonIndex-4, BUTTON_HALL_UP);

            if(isOrderDown==ON && p_elevator->orderArray[buttonIndex][DOWN_BUTTON] == OFF){
                p_elevator->orderArray[buttonIndex][DOWN_BUTTON] = ON;
            }

            if(isOrderUp==ON && p_elevator->orderArray[buttonIndex][UP_BUTTON] == OFF){
                p_elevator->orderArray[buttonIndex][UP_BUTTON] = ON;
            }

        }
    
    }
    return;
}





void updateOrderLights(Elevator *p_elevator) {
    for(int buttonIndex = 0; buttonIndex < NUM_ORDER_BUTTONS; buttonIndex++) {
        if(buttonIndex<4){
            int isOrderCabin = p_elevator->orderArray[buttonIndex][DOWN_BUTTON];
            setOrderButtonLamp(buttonIndex, BUTTON_CAB, isOrderCabin);

        }
        else{
            int isOrderDown = p_elevator->orderArray[buttonIndex][DOWN_BUTTON];
            int isOrderUp = p_elevator->orderArray[buttonIndex][UP_BUTTON];
            if((buttonIndex-4)!=0){
            setOrderButtonLamp(buttonIndex-4, BUTTON_HALL_DOWN, isOrderDown);
            }
            if((buttonIndex-4)!=3){
            setOrderButtonLamp(buttonIndex-4, BUTTON_HALL_UP, isOrderUp);
            }
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
    for(int i =p_elevator->currentFloor; i< NUM_ORDER_BUTTONS; i++) {
        if(p_elevator->orderArray[i][UP_BUTTON] == ACTIVE_ORDER) {
            return ORDER_UP_ABOVE;
        }
    }
    
    for(int i = 0; i< p_elevator->currentFloor; i++) {
        if(p_elevator->orderArray[i][UP_BUTTON] == ACTIVE_ORDER) {
            return ORDER_UP_BELOW;
        }
    }


    return NO_ORDERS;

}


int orderDownwards(Elevator *p_elevator){
    for(int i = 0; i< p_elevator->currentFloor; i++) {
        if(p_elevator->orderArray[i][DOWN_BUTTON] == ACTIVE_ORDER) {
            return ORDER_DOWN_BELOW;
        }
    }

    for(int i = p_elevator->currentFloor; i< NUM_ORDER_BUTTONS; i++) {
        if(p_elevator->orderArray[i][DOWN_BUTTON] == ACTIVE_ORDER) {
            return ORDER_DOWN_ABOVE;
        }
    }
    
    return NO_ORDERS;

}



MotorDirection chooseDirection(Elevator *p_elevator) {

    int currentDirection = p_elevator->currentDirection;
    int lastDirection = p_elevator->lastDirection;
    int currentFloor = p_elevator->currentFloor;

    switch(lastDirection){
        case DIRN_UP:

            if(orderUpwards(p_elevator)==ORDER_UP_ABOVE){
                return DIRN_UP;
            }

            else if(orderDownwards(p_elevator)==ORDER_DOWN_ABOVE){
                return DIRN_UP;
            }

            else if(orderUpwards(p_elevator)==ORDER_UP_BELOW || orderDownwards(p_elevator)==ORDER_DOWN_BELOW){
                return DIRN_DOWN;
            }
            return DIRN_STOP;
        break;

        case DIRN_DOWN:

            if(orderDownwards(p_elevator)==ORDER_DOWN_BELOW){
                return DIRN_DOWN;
            }

            else if(orderUpwards(p_elevator)==ORDER_UP_BELOW){
                return DIRN_DOWN;
            }

            else if(orderUpwards(p_elevator)==ORDER_UP_ABOVE || orderDownwards(p_elevator)==ORDER_DOWN_ABOVE){
                return DIRN_UP;
            }
            return DIRN_STOP;
        break;

        case DIRN_STOP:

            if(orderUpwards(p_elevator)==ORDER_UP_ABOVE || orderDownwards(p_elevator) == ORDER_DOWN_ABOVE){
                return DIRN_UP;
            }

            else if(orderDownwards(p_elevator)==ORDER_DOWN_BELOW || orderUpwards(p_elevator) == ORDER_UP_BELOW){
                return DIRN_DOWN;
            }

            return DIRN_STOP;
        break;
    }






    updateOrderArray(p_elevator);
    int currentDirection = p_elevator->currentDirection;
    int isOrderDown = orderDownwards(p_elevator);
    int isOrderUp = orderUpwards(p_elevator);
    int currentFloor = p_elevator->currentFloor;

    if( (currentDirection == DIRN_DOWN || currentDirection == DIRN_STOP) && isOrderDown==1){
        
         return DIRN_DOWN;
    }

    else if ( (currentDirection == DIRN_UP || currentDirection == DIRN_STOP) && isOrderUp==1) {
     
        return DIRN_UP;
    }

    else {
        
        return DIRN_STOP;
    }

}

void printArray(Elevator *p_elevator){
    for(int i=0;i<NUM_ORDER_BUTTONS;i++){
        for(int j=0; j<NUM_DIRECTIONS; j++){
        
            printf("%d", p_elevator->orderArray[i][j]);
        
        }
    }
    return;
}