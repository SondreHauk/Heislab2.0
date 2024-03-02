#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/direction_control.h"
#include "driver/elevator.h"
#include "driver/queue.h"
#include "driver/button.h"
#include "driver/doors.h"
#include "driver/stop.h"

int main(){
    elevio_init();
    // test
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    //Lager en instans av elevator.
    elevator * elev = elevator_setup_maker();

    //Setter alle knapper til 0.
    reset_all_buttons(elev);

    /*initialisering: Hvis heisen befinner seg mellom etasjer, vil den bevege seg ned
    til den er i en etasje, så sette state til IDLE. */
    if(elevio_floorSensor() == -1){
        while(elevio_floorSensor() == -1){
            elevio_motorDirection(DIRN_DOWN);
        }
        elevio_motorDirection(DIRN_STOP);
        elev->state = IDLE;
    }
    else{
        elev->state = IDLE;
    }

    while(1){
        //Sjekker om stop er trykket inn og setter state til STOP
        STOP_status(elev);
        //Oppdaterer alle knappene i matrisen
        updateAllButtons(elev);
        //Oppdaterer current, previous og inbetween floors
        update_floors(elev);

        MotorDirection direction = elev->current_direction;
        elev_state state = elev->state;
        int order = elev->next_stop;
        int temp_order = elev->temporary_stop;
        int current_floor = elev->current_floor;
        int prev_floor = elev->prev_floor;
        int between_floors = elev->between_floors; //1 if between floors, 0 if not

        switch (state)
        {
        case IDLE:
            if(empty_queue_check(elev) == 0){
                break;
            }
            next_stop(elev); //Setter neste stopp til etasjen med knapp trykket inn
            if(order != current_floor){
                state = MOVING;
            }
            else{
                state = DOORS;
            }
            
            break;
        
        case MOVING:

            /* 
            Sets a direction, UP or DOWN, for elevator to move
            Checks for stops in the direction of movement, and sets state to DOORS if a stop is found
            Checks if the elevator has arrived at the next stop, and sets state to DOORS if it has
             */

            update_direction(elev);            
            same_dir_stop(elev);
            arrival_stop(elev);

            break;
        
        case DOORS:
            /* open doors, wait for 3 seconds, close doors */
            open_doors(elev);
            if(elev->state = DOORS){
                delay(3000);
            }
            elevio_doorOpenLamp(0);
            if(empty_queue_check(elev) == 1){
                elev->state = MOVING;
            }
            else{
                elev->state = IDLE;
            }
            
            break;
        
        case STOP:
            /*
            [S4] Stops elevator
            [D3] Open doors if in a floor
            [S5] Resets all order buttons

            [L6] Lights the stop lamp as long as stopButton is pushed
            [S6] Resets all new orders (ignores new orders)

            [S7] After stop button is released, go to IDLE.
            */

            elevio_motorDirection(0);
            STOP_doors(elev);
            reset_all_buttons(elev);

            while (elevio_stopButton() == 1)
            {
                elevio_stopLamp(1);
            }
            
            state = IDLE;
        
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
            elevio_stopLamp(0);      
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

