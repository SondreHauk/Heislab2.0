#pragma once
#include "elevio.h"
#include <stdio.h>
#include <stdlib.h>


typedef enum{
    IDLE,
    MOVING,
    STOP,
    DOORS,
    INIT
}elev_state;

typedef struct elevator
{
    int current_floor;
    int prev_floor;
    int between_floors;
    MotorDirection current_direction;
    int next_stop;
    int STOP;
    int door;
    int buttons[4][3];
    elev_state state;

} elevator;

elevator * elevator_setup_maker();

void update_direction(elevator * elev);

void update_floors(elevator * elev);

void update_light(elevator * elev, int floor);