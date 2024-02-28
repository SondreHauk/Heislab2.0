#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/direction_control.h"
#include "driver/elevator.h"
#include "driver/queue.h"
#include "driver/button.h"

int main(){
    elevio_init();

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    //Lager en instans av elevator som vi kan bruke til å hente og sette verdier i.
    elevator * elev = elevator_setup_maker();
    reset_all_buttons(elev);

    while(1){
        
        updateAllButtons(elev);
        update_floors(elev);

        MotorDirection direction = elev->current_direction;
        elev_state state = elev->state;
        int order = elev->next_stop;
        int current_floor = elev->current_floor;
        int prev_floor = elev->prev_floor;
        int between_floors = elev->between_floors; //1 if between floors, 0 if not

        switch (state)
        {
        case IDLE:
            reset_current_floor_buttons(elev); //Setter alle knapper på nåværende etasje til 0
            next_stop(elev); //Setter neste stopp til etasjen med knapp trykket inn
            if(order != current_floor){
            state = MOVING;
            }
            else{
                state = DOORS;
            }
            break;
        case MOVING:
            /* check for orders in same direction, update temporary order.
            For every new floor, run same_direction_stop(elev) */
            if (between_floors == 0 && current_floor != prev_floor){
                same_direction_stop(elev);
            }
            if (order == current_floor){
                state = DOORS;
            }
            break;
        case DOORS:
            /* open doors, wait for 3 seconds, close doors */
            state = IDLE;
            break;
        case STOP:
            /* do STOP stuff. Like deleating all orders etc. */
            break;
        default:
            break;
        }


        /*update_direction(elev_states);
        elevio_motorDirection(elev_states->current_direction);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP); 
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }void reset_floor_buttons(states * elev_states)
        //De to funksjonene over tar inn enten DIRN_UP eller DIRN_DOWN for å styre retningen på heisen

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

*/
        if(elevio_obstruction()){
            elevio_stopLamp(1);      
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

