#include "elevator.h"
#include <time.h>




//Elev_io functins
void setElevatorDirection(MotorDirection dir) {
    elevio_motorDirection(dir);
    return;
}

void setButtonLamp(int floor, ButtonType button, int value){
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

void setStopButton(int value){
    elevio_stopButtonLamp(value);
    return;
}

int getOrderButtons(int floor, ButtonType button){
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
    elevio_motorDirection(DIRN_UP);

    while(p_elevator->currentFloor!=-1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
 
}