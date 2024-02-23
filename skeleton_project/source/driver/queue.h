#pragma once
#include "elevator_states.h"

enum floor_request_direction {
    IDLE,
    DOWN,
    UP
};

/*typedef struct outside_request{
    int floor;
    enum floor_request_direction floor_dir;

} OUT_REQ;
*/
typedef struct{
    int buttons_pushed[4][3];
    enum floor_request_direction dir;
    int floor;
} QUEUE;

QUEUE * queue_setup_maker(states * elev_states);

void reset_floor_buttons(QUEUE * queue, int floor);

int * check_for_stops(QUEUE * queue);


