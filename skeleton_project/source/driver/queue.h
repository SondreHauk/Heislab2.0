#pragma once
#include "elevator.h"

typedef struct queue{
    int buttons[4][3];
    int floor;
    MotorDirection dir;
} QUEUE;

QUEUE * queue_setup_maker(elevator * elev_states);

void next_stop(elevator * elev_states);
void arrival_stop(elevator * elev); 
void same_dir_stop(elevator * elev);

//void same_direction_stop(elevator * elev_states);

int empty_queue_check(elevator * elev);

//void same_direction_stop(elevator * elev_states);

/*
enum floor_request_direction {
    IDLE,
    DOWN,
    UP
};

/*typedef struct outside_request{
    int floor;
    enum floor_request_direction floor_dir;

 OUT_REQ;
*/
/*typedef struct{
    int buttons_pushed[4][3];
    enum floor_request_direction dir;
    int floor;
} QUEUE;


QUEUE * queue_setup_maker(states * elev_states);

void reset_floor_buttons(QUEUE * queue, int floor);

int check_for_stops(QUEUE * queue);
*/