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

        if(checkTimer() == 0 && getObstructionButton == OFF){
            setDoorOpenLamp(OFF);
            updateOrderArray(fsm->p_elevator);
            updateOrderLights(fsm->p_elevator);
            // Sett etasjelys ??
            MotorDirection nextDirection = chooseDirection(fsm->p_elevator);
            setElevatorDirection(nextDirection);
            fsm->currentState = MOVING;
        }

        break;
    
    case MOVING:
        if(getStopButton==ON){
            setElevatorDirection(DIRN_STOP);
            fsm->currentState=EMERGENCY;
            break;
        }

        updateOrderArray(fsm->p_elevator);
        updateOrderLights(fsm->p_elevator);

        if(getFloor()!=BETWEEN){
            fsm->p_elevator->currentFloor=getFloor();
        }

        setFloorLamp(fsm->p_elevator->currentFloor);

        if(shouldStop(fsm->p_elevator)==1){
            setElevatorDirection(DIRN_STOP);
            setDoorOpenLamp(ON);
            // setTimer();
            fsm->currentState=IDLE;
            break;
        }

        break;
    
    case EMERGENCY:
        //Turn on light
        setStopLamp(ON);

        //Stop motor
        setElevatorDirection(STOP);

        //If at floor, open door
        if(getFloor()!=BETWEEN){
            setDoorOpenLamp(ON);
        }

        //Check if clicked
        if(getStopButton()==OFF){
            setStopLamp(OFF);
            clearOrders(fsm->p_elevator);   // clear orders function
            updateOrderLights(fsm->p_elevator);
            //setTimer();
            fsm->currentState=IDLE;
            break;
        }
        break;
    
    default:
        fsm->currentState=IDLE;
        break;
    }
}