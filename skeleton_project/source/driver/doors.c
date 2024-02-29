#include "doors.h"


void open_doors(elevator * elev){
    if(elevio_floorSensor() == -1){
        elev->state = MOVING;
    }
    else{
        reset_current_floor_buttons(elev);
        elevio_doorOpenLamp(1);
    }
}

