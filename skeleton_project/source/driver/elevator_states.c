#include "elevator_states.h"
#include "direction_control.h"

//Kode generert av GitHub Copilot
states * elevator_setup_maker(){
    states * elev_states = malloc(sizeof(states));
    elev_states->current_floor = 0;
    elev_states->current_direction = 0;
    elev_states->next_stop = 0;
    elev_states->STOP = 0;
    elev_states->door = 0;
    for (int i = 0; i < 4; i++){
        elev_states->inside_lights[i] = 0;
        elev_states->outside_ligst[i] = 0;
        elev_states->inside_requests[i] = 0;
        elev_states->outside_requests[i] = 0;
    }
    elev_states->outside_requests_updated = 0;
    elev_states->inside_requests_updated = 0;
    return elev_states;
}

void update_direction(states * elev_states){
    int STOP = elev_states->STOP;
    int current_floor = elev_states->current_floor;
    int next_stop = elev_states->next_stop;
    MotorDirection old_direction = elev_states->current_direction;
    elev_states->current_direction = update_current_direction(STOP, old_direction, current_floor, next_stop);
}