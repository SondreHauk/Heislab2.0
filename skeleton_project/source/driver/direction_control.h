#pragma once
#include "elevio.h"
#include "elevator.h"

MotorDirection update_current_direction(int current_floor, int next_order);

void update_direction(elevator * elev);