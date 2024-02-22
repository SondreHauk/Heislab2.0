#pragma once
#include "elevio.h"

void update_current_direction(int STOP, MotorDirection *current_direction, int current_floor, int next_order);
int get_current_direction();