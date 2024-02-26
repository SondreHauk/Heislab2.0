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

    //elevio_motorDirection(DIRN_UP);

    elevator * elev = elevator_setup_maker(); //Lager en instans av elev_states som vi kan bruke til å hente og sette verdier i.
    reset_all_buttons(elev);

    while(1){
        updateAllButtons(elev);
        int floor = elevio_floorSensor();
        int direction = elev->current_direction;
        //Kan sette inn en queue og direction control her som til sammen lager en DIRN_IP, en DIRN_DOWN eller IDLE.
        //Denne kan så settes inn i eleviomotor_Direction(MotorDirection) som så generer et pådrag til heisen. 
        //Queue function returning next stop.
        //Må lage en instans av elev_states kalt states eller noe.

        elev_state state = IDLE;

        switch (state)
        {
        case IDLE:
            reset_floor_buttons(elev);
            next_stop(elev);
            if(elev->next_stop != elev->current_floor){
            elev->state = MOVING;
            }
            else{
                elev->state = DOORS;
            }
            break;
        case MOVING:
            /* check for orders in same direction, update orders */
            elev->state = DOORS;
            break;
        case DOORS:
            /* open doors, wait for 3 seconds, close doors */
            elev->state = IDLE;
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
