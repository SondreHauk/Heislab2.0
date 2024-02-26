#include "button.h"

void updateButton(int floor, ButtonType button_type, states * elev_states) {
    elev_states->buttons[floor][button_type] = elevio_callButton(floor, button_type); //updates button status
    elevio_buttonLamp(floor, button_type, elev_states->buttons[floor][button_type]); //updates the same lamp

}

void updateAllButtons(states * elev_states){
    for (int i = 0; i < N_FLOORS; i++){
        for(int j = 0; j < N_BUTTONS; j++){
            updateButton(i, j, elev_states);
        }
    }
}