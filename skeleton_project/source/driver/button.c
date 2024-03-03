#include "button.h"
#include <assert.h>

void updateButton(int floor, ButtonType button_type, elevator * elev_states) {
    if(elevio_callButton(floor, button_type) == 1){
        elev_states->buttons[floor][button_type] = elevio_callButton(floor, button_type); //updates button status
        elevio_buttonLamp(floor, button_type, elev_states->buttons[floor][button_type]); //updates the same lamp
    }
}

void updateAllButtons(elevator * elev_states){
    for (int i = 0; i < N_FLOORS; i++){
        for(int j = 0; j < N_BUTTONS; j++){
            updateButton(i, j, elev_states);
        }
    }
}

void reset_current_floor_buttons(elevator * elev){
    if(elev->current_floor != -1){ //Make sure the elevator is at an actual floor
        for(int i = 0; i < N_BUTTONS; i++){
            elev->buttons[elev->current_floor][i] = 0;
            elevio_buttonLamp(elev->current_floor, i, 0);
        }
    }
}

void reset_all_buttons(elevator * elev_states){
    for(int i = 0; i < N_FLOORS; i++){
        for(int j = 0; j < N_BUTTONS; j++){
            elev_states->buttons[i][j] = 0;
            elevio_buttonLamp(i, j, 0);
        }
    }
}