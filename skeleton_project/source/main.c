#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"
#include "FSM.h"
#include "timer.h"




int main(){

    elevio_init();
    
    Elevator *p_elevator=malloc(sizeof(Elevator));
    FSM *p_fsm=malloc(sizeof(FSM));
    Timer *p_timer = malloc(sizeof(Timer));

    setTimer(p_timer);

    elevatorInit(p_elevator);
        
    
    while(1){
         FSMSwitch(p_fsm, p_elevator, p_timer);
    }

    
    free(p_elevator);
    free(p_fsm);
    free(p_timer);
    return 0;
}

    