#include "doors.h"
#include <time.h>


void open_doors(elevator * elev){
    /*if(elevio_floorSensor() == -1){
        elev->state = MOVING;
    }
    else{
        reset_current_floor_buttons(elev);
        elevio_doorOpenLamp(1);
    }*/
    if(elevio_floorSensor() != -1){
        reset_current_floor_buttons(elev);
        elevio_doorOpenLamp(1);
        nanosleep(&(struct timespec){3, 0}, NULL); 
        elevio_doorOpenLamp(0);
    }
}

