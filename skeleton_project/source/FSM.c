#include "FSM.h"
#include "elevator.h"
/**
 * @brief FSM.c
 * 
 */

void FSMSwitch(State currentState, Elevator *p_elevator){
    switch (currentState)
    {
    case IDLE:
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
        else{
            setDoorOpenLamp(OFF);
        }

        //clear orders function
        clearOrders(p_elevator);

        //Check if clicked
        if(getStopButton()==OFF){
            setStopLamp(OFF);
           
            //Check if it is on floor, then timer for door
             if(getFloor()!=BETWEEN){
                //timer
                setDoorOpenLamp(OFF);
            }

            currentState=IDLE;
            break;
        }
        break;
    
    default:
        break;
    }
}