#include "elevator_states.h"
#include "direction_control.h"

void update_direction(states * elev_states){
    int STOP = elev_states->STOP;
    int current_floor = elev_states->current_floor;
    int next_stop = elev_states->next_stop;
    MotorDirection old_direction = elev_states->current_direction;
    elev_states->current_direction = update_current_direction(STOP, old_direction, current_floor, next_stop);
}