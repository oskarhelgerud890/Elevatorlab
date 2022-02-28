#include "FSM.h"
#include "elevator.h"
/**
 * @brief FSM.c
 * 
 */

void FSMSwitch(State currentState, Elevator *p_elevator){
    switch (currentState){
    case IDLE:

        if(getStopButton){
            currentState = EMERGENCY;
            break;
        }

        

        break;
    
    case MOVING:
        break;
    
    case EMERGENCY:
        //Turn on light
        setStopLamp(ON);

        //Stop motor
        setElevatorDirection(STOP);

        //If at place, open door
        if(getFloor()!=BETWEEN){
            setDoorOpenLamp(ON);
        }

        //clear orders function
        clearOrders(p_elevator);

        //Check if clicked
        if(getStopButton()==OFF){
            setStopLamp(OFF);
            currentState=IDLE;
            break;
        }
        break;
    
    default:
        currentState=IDLE;
        break;
    }
}