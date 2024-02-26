#pragma once
#include <elevio.h>
#include "elevator_states.h"

void updateButton(int floor, ButtonType button_type, states * elev_states);

void updateAllButtons(states * elev_states);