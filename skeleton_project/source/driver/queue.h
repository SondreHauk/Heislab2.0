#pragma once
#include "elevator_states.h"

enum floor_request_direction {
    IDLE,
    DOWN,
    UP
};

typedef struct outside_request{
    int floor;
    enum floor_request_direction floor_dir;
} OUT_REQ;

typedef struct queue{
    int floor_directions[4][2];
    int next_floor;
    OUT_REQ cron_order[6];
    int inside_requests[4];
    int current_floor;

} QUEUE;

QUEUE * queue_setup_maker(states * elev_states);