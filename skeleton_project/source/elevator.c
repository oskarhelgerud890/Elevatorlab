#include "elevator.h"

/**
* @brief Set elevator direction. Wrapper function for
* the elevio library.
*/

int setElevatorDirection(MotorDirection dir) {
    elevio_motorDirection(dir);
}
