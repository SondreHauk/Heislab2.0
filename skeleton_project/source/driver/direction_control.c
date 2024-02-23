#include "direction_control.h"

MotorDirection update_current_direction(int STOP, MotorDirection current_direction, int current_floor, int next_order){
    if (STOP == 0){
        if (current_floor == next_order){
            current_direction = 0;
        }
        if (current_floor < next_order){
            current_direction = 1;
        }
        if (current_floor > next_order){
            current_direction = -1;
        }
    }
    else{
        current_direction = 0;
    }
}

MotorDirection get_current_direction(MotorDirection current_direction){
    return current_direction;
}