#include "direction_control.h"

MotorDirection update_current_direction(int current_floor, int next_order){
    MotorDirection new_direction;
    if (current_floor == next_order){
        new_direction = DIRN_STOP;
    }
    if (current_floor < next_order){
        new_direction = DIRN_UP;
    }
    if (current_floor > next_order){
        new_direction = DIRN_DOWN;
    }
    /*else{
        new_direction = 0;
    }*/
    return new_direction;
}

/*void update_direction(elevator * elev){
    int current_floor = elev->current_floor;
    int next_order = elev->next_stop;
    int current_direction = elev->current_direction;
    if (current_floor == next_order){
        current_direction = 0;
    }
    if (current_floor < next_order){
        current_direction = 1;
    }
    if (current_floor > next_order){
        current_direction = -1;
    }
    elevio_motorDirection(current_direction);
}*/