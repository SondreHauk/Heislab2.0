#include "queue.h"

QUEUE * queue_setup_maker(elevator * elev_states){
    QUEUE * queue_new = (QUEUE *)malloc(sizeof(QUEUE));
    queue_new->floor = elev_states->current_floor;
    queue_new->dir = elev_states->current_direction;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            queue_new->buttons[i][j] = 0;
        }
    }
    return queue_new;
}

int same_direction_stop(elevator * elev){
    int next_stop;
    if(elev->current_direction == 1){
        for(int i = elev->current_floor; i < 4; i++){
            if(elev->buttons[i][0] == 1 || elev->buttons[i][1] == 1){
                next_stop = i;
                break;
            }
        }
    }
    if(elev->current_direction == -1){
        for(int i = elev->current_floor; i > -1; i--){
            if(elev->buttons[i][0] == 1 || elev->buttons[i][2] == 1){
                next_stop = i;
                break;
            }
        }
    }
    return next_stop;
}



void next_stop(elevator * elev){
    int next_stop;
    int current_floor = elev->current_floor;
    int current_direction = elev->current_direction;
    for(int i = 0; i < 4; i++){
        if(elev->buttons[i][0] == 1 || elev->buttons[i][1] == 1 || elev->buttons[i][2] == 1){
            next_stop = i;
            break;
        }
    }
    elev->next_stop = next_stop;
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


