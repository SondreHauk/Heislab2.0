#include "queue.h"

//Lager den første que-en når programmet starter opp.
QUEUE * queue_setup_maker(states * elev_states){
    QUEUE * queue_new = (QUEUE *)malloc(sizeof(QUEUE));
    for(int i = 0; i < 4; i++){
        for(int j = 0; i < 3; j++){
            queue_new->buttons_pushed[i][j] = 0;
        }
    }
    return queue_new;
}

update_queue(QUEUE * queue, states states){

}

//Nullstiller alle knappene i etasjen heisen stopper i
void reset_floor_buttons(QUEUE * queue, int floor){
    for(int i = 0; i < 3; i++){
        queue->buttons_pushed[floor-1][i] = 0;
    }
}

int check_for_stops(QUEUE * queue){
    int next_stop;
    if(queue->dir = DOWN){
        for(int i = queue->floor; i > -1; i--){
            if(queue->buttons_pushed[i][1] == 1 || queue->buttons_pushed[i][2] == 1){
                next_stop = i + 1;
                break;
            }
        }
    }
    elif(queue->dir = UP){
        for(int i = queue->floor; i < 4; i+){
            if(queue->buttons_pushed[i][1] == 1 || queue->buttons_pushed[i][2] == 1){
                next_stop = i + 1;
                break;
            }
        }
    }
}
