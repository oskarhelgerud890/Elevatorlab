#include "FSM.h"
#include "elevator.h"


/**
 * @brief FSM.c
 * 
 */

void FSMSwitch(FSM *p_fsm, Elevator *p_elevator, Timer *p_timer){
    switch (p_fsm->currentState){
    case IDLE:
        if(getStopButton()){
            p_fsm->currentState = EMERGENCY;
            break;
        }
        

        updateOrderArray(p_elevator);
        updateOrderLights(p_elevator);


        int door = p_elevator->doorOpen;
        int time = checkTimer(TIME_TO_ELAPSE, p_timer);
        int obstruction = getObstructionButton();

        if(time == TIME_NOT_OUT){
            clearOrdersOnFloor(p_elevator);
            updateOrderLights(p_elevator);
        }

        if(door == OFF || (time == TIME_OUT && obstruction == OFF)){
            setDoorOpenLamp(OFF);
            p_elevator->doorOpen = OFF;
            MotorDirection nextDirection = chooseDirection(p_elevator);
            if(nextDirection!= DIRN_STOP){
                p_elevator->lastDirection = p_elevator->currentDirection;
                p_elevator->currentDirection=nextDirection;
                p_fsm->currentState = MOVING;
            }
        }

        else if(door == ON && obstruction == ON) {
            setTimer(p_timer);

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
                p_elevator->doorOpen=ON;
                setTimer(p_timer);
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
            p_elevator->doorOpen = ON;
        }

        //Check if clicked
        if(getStopButton()==OFF){
            setStopLamp(OFF);
            setTimer(p_timer);
            p_fsm->currentState=IDLE;
            break;
        }
        break;
    
    default:
        p_fsm->currentState=IDLE;
        break;
    }
}