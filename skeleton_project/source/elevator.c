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
    p_elevator->currentObstructionValue=OFF;
    p_elevator->lastObstructionValue=OFF;
    p_elevator->currentDirection=DIRN_STOP;
    p_elevator->lastDirection = DIRN_STOP;
    p_elevator->doorOpen = OFF;

    return;
}



void updateOrderArray(Elevator *p_elevator){
    for(int buttonIndex = 0; buttonIndex < NUM_ORDER_BUTTONS; buttonIndex++){
        
        // The first 4 rows in the order array correspond to the order buttons in the cabin.
        if(buttonIndex<4){
        
            int isOrderCabin = getOrderButton(buttonIndex, BUTTON_CAB);

            if(isOrderCabin==ON && p_elevator->orderArray[buttonIndex][DOWN_BUTTON]==OFF){
                p_elevator->orderArray[buttonIndex][DOWN_BUTTON] = ON;
                p_elevator->orderArray[buttonIndex][UP_BUTTON] = ON;
            }


        }
        else{
            // The rest of the buttons ...
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


int orderAbove(Elevator *p_elevator){
    

    for(int i =p_elevator->currentFloor+1; i< NUM_FLOORS; i++) {
        if(p_elevator->orderArray[i][UP_BUTTON] == ACTIVE_ORDER || p_elevator->orderArray[i][DOWN_BUTTON] == ACTIVE_ORDER) {
            return ACTIVE_ORDER;
        }
    }

    for(int i=p_elevator->currentFloor+5; i<NUM_ORDER_BUTTONS; i++) {
        if(p_elevator->orderArray[i][UP_BUTTON] == ACTIVE_ORDER || p_elevator->orderArray[i][DOWN_BUTTON] == ACTIVE_ORDER) {
            return ACTIVE_ORDER;
        }

    }

    return NO_ORDERS;
}


int orderBelow(Elevator *p_elevator){
    for(int i = 0; i< p_elevator->currentFloor; i++) {
        if(p_elevator->orderArray[i][DOWN_BUTTON] == ACTIVE_ORDER  || p_elevator->orderArray[i][UP_BUTTON] == ACTIVE_ORDER) {
            return ACTIVE_ORDER;
        }
    }

    for(int i = 4; i< p_elevator->currentFloor+4; i++) {
        if(p_elevator->orderArray[i][DOWN_BUTTON] == ACTIVE_ORDER  || p_elevator->orderArray[i][UP_BUTTON] == ACTIVE_ORDER) {
            return ACTIVE_ORDER;
        }
    }   

    return NO_ORDERS;
}

int orderOnCurrentFloor(Elevator *p_elevator){
    int cabinButton = p_elevator->orderArray[p_elevator->currentFloor][UP_BUTTON];
    int hallUpButton = p_elevator->orderArray[p_elevator->currentFloor+4][UP_BUTTON];
    int hallDownButton = p_elevator->orderArray[p_elevator->currentFloor+4][DOWN_BUTTON];

    if((cabinButton || hallDownButton || hallUpButton) == ACTIVE_ORDER) {
        return ACTIVE_ORDER;
    }

    return NO_ORDERS;
}

int shouldStop(Elevator *p_elevator){

    int currentDirection = p_elevator->currentDirection;
    int currentFloor = p_elevator->currentFloor;
    int LowerOrder = orderBelow(p_elevator);
    int HigherOrder = orderAbove(p_elevator);

    int cabinButton = p_elevator->orderArray[currentFloor][UP_BUTTON];
    int hallUpButton = p_elevator->orderArray[currentFloor+NUM_FLOORS][UP_BUTTON];
    int hallDownButton = p_elevator->orderArray[currentFloor+NUM_FLOORS][DOWN_BUTTON];
    int orderOnFloor = orderOnCurrentFloor(p_elevator);


    switch(currentDirection){
        case DIRN_UP:
            if((cabinButton==ON || hallUpButton==ON) || (hallDownButton == ON & HigherOrder == NO_ORDERS)){
                printf("STOPPING 0");
                return STOP;
            }

            break;

        case DIRN_DOWN:
            if(cabinButton==ON || hallDownButton==ON){
                printf("STOPPING 2");
                return STOP;
            }
            else if(cabinButton==ON && LowerOrder==NO_ORDERS || hallUpButton==ON && LowerOrder==NO_ORDERS){
                printf("STOPPING 3");
                return STOP;
            }
            break;
            
        default:
            break;

    }
    return DONT_STOP;

}



MotorDirection chooseDirection(Elevator *p_elevator) {

    int currentDirection = p_elevator->currentDirection;
    int lastDirection = p_elevator->lastDirection;
    int currentFloor = p_elevator->currentFloor;

    switch(lastDirection){
        case DIRN_UP:

            if((orderAbove(p_elevator) || orderOnCurrentFloor(p_elevator)) ==ACTIVE_ORDER){
                return DIRN_UP;
            }

            else if(orderBelow(p_elevator)==ACTIVE_ORDER){
                return DIRN_DOWN;
            }
            return DIRN_STOP;
        break;

        case DIRN_DOWN:

            if(orderBelow(p_elevator)==ACTIVE_ORDER){
                return DIRN_DOWN;
            }

            else if(orderAbove(p_elevator)==ACTIVE_ORDER){
                return DIRN_UP;
            }
            return DIRN_STOP;
        break;

        case DIRN_STOP:
            if((orderOnCurrentFloor(p_elevator) || orderAbove(p_elevator)) == ACTIVE_ORDER) {
                return DIRN_UP;
            }

            else if(orderBelow(p_elevator)==ACTIVE_ORDER){
                return DIRN_DOWN;
            }

            return DIRN_STOP;
        break;
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

void clearOrdersOnFloor(Elevator *p_elevator){
    int currentFloor = p_elevator->currentFloor;
    p_elevator->orderArray[currentFloor][DOWN_BUTTON] = OFF;
    p_elevator->orderArray[currentFloor][UP_BUTTON] = OFF;
    p_elevator->orderArray[currentFloor+4][DOWN_BUTTON] = OFF;
    p_elevator->orderArray[currentFloor+4][UP_BUTTON] = OFF;
    return;
}