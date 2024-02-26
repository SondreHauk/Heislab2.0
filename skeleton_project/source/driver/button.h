#pragma once
#include "elevio.h"
#include "elevator.h"

void updateButton(int floor, ButtonType button_type, elevator * elev_states);

void updateAllButtons(elevator * elev_states);

void reset_floor_buttons(elevator * elev_states);