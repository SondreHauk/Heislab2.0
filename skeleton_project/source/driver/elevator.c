#include "elevator.h"
#include "direction_control.h"
#include "elevio.h"
#include "button.h"
//Kode generert av GitHub Copilot
elevator * elevator_setup_maker(){
    elevator * elev = malloc(sizeof(elevator));
    elev->current_floor = elevio_floorSensor();
    elev->current_direction = 0;
    elev->next_stop = 0;
    elev->STOP = 0;
    elev->door = 0;
    elev->state = INIT;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            elev->buttons[i][j] = 0;
        }
    }
    return elev;
}

void update_direction(elevator * elev){
    int STOP = elev->STOP;
    int current_floor = elev->current_floor;
    int next_stop = elev->next_stop;
    MotorDirection old_direction = elev->current_direction;
    elev->current_direction = update_current_direction(STOP, old_direction, current_floor, next_stop);
}

/*void update_requests(states * elev_states){
    for (int i = 0; i < 4; i++){
        elev_states->inside_requests[i] = elevio_get_button_signal(BUTTON_COMMAND, i);
        elev_states->outside_requests[i] = elevio_get_button_signal(BUTTON_CALL_UP, i);
        elev_states->outside_requests[i] = elevio_get_button_signal(BUTTON_CALL_DOWN, i);
    }
}*/