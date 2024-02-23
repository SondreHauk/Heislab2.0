#pragma once
#include "elevio.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct elevator_states
{
    int current_floor;
    MotorDirection current_direction;
    int next_stop;
    int STOP;
    int door;
    int inside_lights[4];
    int outside_ligst[4];
    int inside_requests[4];
    int outside_requests[4];
    int outside_requests_updated;
    int inside_requests_updated;
    
} states;


void update_direction(states * elev_states);