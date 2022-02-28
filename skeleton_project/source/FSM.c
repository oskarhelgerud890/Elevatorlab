#include "FSM.h"
#include "elevator.h"
/**
 * @brief FSM.c
 * 
 */

void FSMSwitch(FSM *fsm){
    switch (fsm->currentState){
    case IDLE:

        if(getStopButton){
            fsm->currentState = EMERGENCY;
            break;
        }

        break;
    
    case MOVING:
        if(getStopButton==ON){
            fsm->currentState=EMERGENCY;
            setElevatorDirection(DIRN_STOP);
            break;
        }

        updateorderArray(fsm->p_elevator);

        if(getFloor()!=BETWEEN){
            fsm->p_elevator->currentFloor=getFloor();
        }

        setFloorLamp(fsm->p_elevator->currentFloor);

        if(shouldStop(fsm->p_elevator)==1){
            setElevatorDirection(DIRN_STOP);
            fsm->currentState=IDLE;
            break;
        }

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
        clearOrders(fsm->p_elevator);

        //Check if clicked
        if(getStopButton()==OFF){
            setStopLamp(OFF);
            fsm->currentState=IDLE;
            break;
        }
        break;
    
    default:
        fsm->currentState=IDLE;
        break;
    }
}