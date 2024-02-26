#pragma once

//Skulle gjerne hatt en algoritme som returnerer en matrise med alle lysene
//må nok bruke funskjonen elevio_button_lamp()
//Kan man bruke samme matrise som i structen QUEUE?

struct elevator_lights
{
    int lights[4][3];
} lights;


int update_inside_lights();
int update_outside_lights();

elevator_lights update_all_lights(); 