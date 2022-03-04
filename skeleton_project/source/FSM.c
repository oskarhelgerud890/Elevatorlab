#include "FSM.h"
#include "elevator.h"
/**
 * @brief FSM.c
 * 
 */

void FSMSwitch(FSM *p_fsm, Elevator *p_elevator){
    switch (p_fsm->currentState){
    case IDLE:
        if(getStopButton()){
            p_fsm->currentState = EMERGENCY;
            break;
        }
        

        updateOrderArray(p_elevator);
        updateOrderLights(p_elevator);

        if(getObstructionButton() == OFF){
            setDoorOpenLamp(OFF);
            MotorDirection nextDirection = chooseDirection(p_elevator);
            p_elevator->lastDirection = p_elevator->currentDirection;
            p_elevator->currentDirection=nextDirection;

            
            if(p_elevator->currentDirection!=DIRN_STOP){
                p_fsm->currentState = MOVING;
            }
            
        }

        break;
    
    case MOVING:
    
        if(getStopButton()==ON){
            setElevatorDirection(DIRN_STOP);
            p_fsm->currentState=EMERGENCY;
            break;
        }
        setElevatorDirection(p_elevator->currentDirection);
        updateOrderArray(p_elevator);
        updateOrderLights(p_elevator);

        if(getFloor()!=BETWEEN){
            p_elevator->currentFloor=getFloor();
        

            setFloorLamp(p_elevator->currentFloor);

            if(shouldStop(p_elevator)==STOP){
                setElevatorDirection(DIRN_STOP);
                p_elevator->lastDirection=p_elevator->currentDirection;
                p_elevator->currentDirection=DIRN_STOP;

                setDoorOpenLamp(ON);
                //setTimer();
                clearOrdersOnFloor(p_elevator);
                updateOrderLights(p_elevator);
                p_fsm->currentState=IDLE;
                break;
            }
        }

        break;
    
    case EMERGENCY:
        //Turn on light
        setStopLamp(ON);

        //Stop motor
        setElevatorDirection(STOP);

        clearOrders(p_elevator);   // clear orders function

    
        updateOrderLights(p_elevator);

        //If at floor, open door
        if(getFloor()!=BETWEEN){
            setDoorOpenLamp(ON);
        }

        //Check if clicked
        if(getStopButton()==OFF){
            setStopLamp(OFF);
            //setTimer();
            p_fsm->currentState=IDLE;
            break;
        }
        break;
    
    default:
        p_fsm->currentState=IDLE;
        break;
    }
}