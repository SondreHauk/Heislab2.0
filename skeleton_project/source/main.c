#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/direction_control.h"
#include "driver/elevator_states.h"
#include "driver/queue.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    states * elev_states = elevator_setup_maker(); //Lager en instans av elev_states som vi kan bruke til å hente og sette verdier i.

    QUEUE * queue = queue_setup_maker(elev_states); //Lager en instans av queue som vi kan bruke til å hente og sette verdier i.

    while(1){
        int floor = elevio_floorSensor(); //Fra denne kan vi hente hvilken etasje vi er i.

        //Kan sette inn en queue og direction control her som til sammen lager en DIRN_IP, en DIRN_DOWN eller IDLE.
        //Denne kan så settes inn i eleviomotor_Direction(MotorDirection) som så generer et pådrag til heisen. 
        //Queue function returning next stop.
        //Må lage en instans av elev_states kalt states eller noe. 
        update_direction(elev_states);

        elevio_motorDirection(elev_states->current_direction);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP); 
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
        //De to funksjonene over tar inn enten DIRN_UP eller DIRN_DOWN for å styre retningen på heisen

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }


        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
