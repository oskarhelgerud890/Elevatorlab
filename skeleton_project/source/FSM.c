#include "FSM.h"
#include "elevator.h"
/**
 * @brief FSM.c
 * 
 */

void FSMSwitch(FSM *fsm, Elevator *p_elevator){
    switch (fsm->currentState){
    case IDLE:
        if(getStopButton()){
            fsm->currentState = EMERGENCY;
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
                fsm->currentState = MOVING;
            }
            printf("Outside func: %d\n",p_elevator->currentDirection);
        }

        break;
    
    case MOVING:
        if(getStopButton()==ON){
            setElevatorDirection(DIRN_STOP);
            fsm->currentState=EMERGENCY;
            break;
        }
        setElevatorDirection(p_elevator->currentDirection);
        updateOrderArray(p_elevator);
        updateOrderLights(p_elevator);

        if(getFloor()!=BETWEEN){
            p_elevator->currentFloor=getFloor();
        }

        setFloorLamp(p_elevator->currentFloor);

        if(shouldStop(p_elevator)==1){
            setElevatorDirection(DIRN_STOP);
            p_elevator->currentDirection=DIRN_STOP;

            setDoorOpenLamp(ON);
            // setTimer();
            //clear orders on floor
            updateOrderLights(p_elevator);
            fsm->currentState=IDLE;
            break;
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
            fsm->currentState=IDLE;
            break;
        }
        break;
    
    default:
        fsm->currentState=IDLE;
        break;
    }
}