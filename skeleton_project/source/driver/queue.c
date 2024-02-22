#include "queue.h"

QUEUE * queue_setup_maker(states * elev_states){
    QUEUE * queue_new = (QUEUE *)malloc(sizeof(QUEUE));
    
    queue_new->current_floor = elev_states -> current_floor;

    return queue_new;
};

update_queue(QUEUE * queue, states states){

};

