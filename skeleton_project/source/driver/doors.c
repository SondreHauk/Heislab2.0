#include "doors.h"


void open_doors(elevator * elev){
    assert(elevio_floorSensor() != -1);
    reset_current_floor_buttons(elev);
    elevio_doorOpenLamp(1);
}

