#include "queue.h"
#include <assert.h>

QUEUE * queue_setup_maker(elevator * elev){
    QUEUE * queue_new = (QUEUE *)malloc(sizeof(QUEUE));
    queue_new->floor = elev->current_floor;
    queue_new->dir = elev->current_direction;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            queue_new->buttons[i][j] = 0;
        }
    }
    return queue_new;
}

/*void same_direction_stop(elevator * elev){
    int temporary_stop = elev->temporary_stop;
    if(elev->current_direction == 1){
        for(int i = elev->current_floor; i < 4; i++){
            if(elev->buttons[i][0] == 1 || elev->buttons[i][1] == 1){
                temporary_stop = i;
                break;
            }
        }
    }
    if(elev->current_direction == -1){
        for(int i = elev->current_floor; i > -1; i--){
            if(elev->buttons[i][0] == 1 || elev->buttons[i][2] == 1){
                temporary_stop = i;
                break;
            }
        }
    }
    elev->temporary_stop = temporary_stop;
}*/

/*Denne funksjon sjekker om man skal stoppe i etasjen man er i
ved å sjekke om det er noen i etasjen som skal samme retning som 
heisen allerede er på vei. Går så til DOORS.*/
void same_dir_stop(elevator * elev){
    int current_floor = elev->current_floor;
    MotorDirection current_direction = elev->current_direction;

    //assert(current_direction == 1 || current_direction == -1);
    //assert(current_floor != -1); 

    ButtonType UP = elev->buttons[current_floor][0];
    ButtonType DOWN = elev->buttons[current_floor][1];
    if (current_direction == 1 && UP == 1){
        current_direction = 0;
        elev->state = DOORS;
    }
    if (current_direction == -1 && DOWN == 1){
        current_direction = 0;
        elev->state = DOORS;
    }
}

/*Sjekker om man er ankommet etasjen til bestillingen, 
dersom man er i rett etasje, blir state satt til DOORS*/
void arrival_stop(elevator * elev){
        if (elev->next_stop == elev->current_floor){
        elev->state = DOORS;
    }
}

void next_stop(elevator * elev){
    int next_stop;
    int current_floor = elev->current_floor;
    int current_direction = elev->current_direction;
    for(int i = 0; i < 4; i++){
        if(elev->buttons[0][i] == 1 || elev->buttons[1][i] == 1 || elev->buttons[0][i] == 1){
            next_stop = i;
            break;
        }
    }
    elev->next_stop = next_stop;
}

int empty_queue_check(elevator * elev){
    int test = 0;
    for(int i = 0; i < N_FLOORS; i++){
        for(int j = 0; j < N_BUTTONS; j++){
            if(elev->buttons[i][j] == 1){
                test = 1;
            }
        }
    }
    if(test == 1){
        return 1;
    }
    else{
        return 0;
    }
}


//Lager den første que-en når programmet starter opp.
/*QUEUE * queue_setup_maker(states * elev_states){
    QUEUE * queue_new = (QUEUE *)malloc(sizeof(QUEUE));
    for(int i = 0; i < 4; i++){
        for(int j = 0; i < 3; j++){
            queue_new->buttons[i][j] = 0;
        }
    }
    return queue_new;
}

update_queue(QUEUE * queue, states states){

}

void reset_floor_buttons(QUEUE * queue, int floor){
    for(int i = 0; i < 3; i++){
        queue->buttons_pushed[floor-1][i] = 0;
    }
}

int check_for_stops(QUEUE * queue){for(int i = 0; i < 4; i++){
        if(queue->buttons[i][0] == 1 || queue->buttons[i][1] == 1 || queue->buttons[i][2] == 1){
            next_stop = i;
            break;
    if(queue->dir = DOWN){
        for(int i = queue->floor; i > -1; i--){
            if(queue->buttons_pushed[i][1] == 1 || queue->buttons_pushed[i][2] == 1){
                next_stop = i + 1;
                break;
            }
        }
    }
    if(queue->dir = UP){
        for(int i = queue->floor; i < 4; i++){
            if(queue->buttons_pushed[i][1] == 1 || queue->buttons_pushed[i][2] == 1){
                next_stop = i + 1;
                break;
            }
        }
    }
}
*/