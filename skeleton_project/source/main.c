#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include "driver/elevio.h"
#include "driver/direction_control.h"
#include "driver/elevator.h"
#include "driver/queue.h"
#include "driver/button.h"
#include "driver/doors.h"
#include "driver/stop.h"

int main(){
    elevio_init();
    //Test
    printf("=== Program Start ===\n");

    //Lager en instans av elevator.
    elevator * elev = elevator_setup_maker();

    //Setter alle knapper til 0.
    reset_all_buttons(elev);

    /*initialisering: 
    Hvis heisen befinner seg mellom etasjer, 
    vil den bevege seg ned til nærmeste etasje, 
    så sette state til IDLE. */

    if(elevio_floorSensor() == -1){               //[O1], [O2], [O3] Oppstart
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
        update_floors(elev);                     //[L3], [L4], [L5] Etasjelys
        //update_direction(elev); //Opphavet til at den gåt ned til 1. etg etter INIT pga update_current_direction funksjonen. Når next order = 0, må den til etg 0 for å stoppe.                 

        MotorDirection direction = elev->current_direction;
        elev_state state = elev->state;
        int order = elev->next_stop;
        int temp_order = elev->temporary_stop;
        int current_floor = elev->current_floor;
        int prev_floor = elev->prev_floor;
        int between_floors = elev->between_floors; //1 if between floors, 0 if not

        switch (elev->state)
        {
        case IDLE:
        
        elevio_doorOpenLamp(0);                   //[D3] Heisedøren skal være lukket når den har ubetjente bestillinger                                  
            if(empty_queue_check(elev) == 0){
                break;
            }
            next_stop(elev);
            if(elev->next_stop != elev->current_floor){
                elev->state = MOVING;
            }
            else{
                elev->state = DOORS;
            }
            if(elevio_stopButton() == 1){
                elev->state = STOP;
            }
            break;
        
        case MOVING:

            /* 
            Sets a direction, UP or DOWN, for elevator to move
            Checks for stops in the direction of movement, and sets state to DOORS if a stop is found
            Checks if the elevator has arrived at the next stop, and sets state to DOORS if it has
             */

            update_direction(elev); 
            if(elevio_floorSensor() != -1){
                same_dir_stop(elev);         
            }           
            //[H2] Heisen betjener kun bestillinger fra Hall som er samme vei  
            arrival_stop(elev);

            break;
        
        case DOORS:
            /* 
            Open doors, wait for 3 seconds, close doors
            It goes from MOVING to DOORS without stopping the elvator
            Need something that stops the elevator!
            */

            elevio_motorDirection(0);             //[S1] Heisen skal alltid stå stille når døren er åpen
            open_doors(elev);                     //[H3], [S2], [D1] Alle bestillinger i etasjen regnes som utført,
                                                  //Døren skal ikke åpne seg utenfor etasje, Åpen i tre sek ved ankomst
                                                   
            /*if(empty_queue_check(elev) == 1){ //Tror denne er opphav til probelm 3! Går rett til moving uten å sette new_stop (dette skjer i IDLE)
                elev->state = MOVING;
            }
            else{*/
                elev->state = IDLE;
            //}
            
            break;
        
        case STOP:

            elevio_motorDirection(0);              //[S4] Stops elevator
            reset_all_buttons(elev);               //[S5] Resets all order buttons
                                                   //[D3] Open doors if in a floor
            if(elevio_floorSensor() != -1){
                while(elevio_stopButton() == 1){
                    elevio_stopLamp(1);
                    elevio_doorOpenLamp(1);
                }
                elevio_stopLamp(0);
                elev->state = DOORS;
            }
            else{
                while (elevio_stopButton() == 1)       //[L6] Lights the stop lamp as long as stopButton is pushed
                {                                      //[S6] Resets all new orders (ignores new orders) 
                    elevio_stopLamp(1);                 
                }   
                elevio_stopLamp(0);                    //[S7] After stop button is released, go to IDLE.
                elev->state = IDLE;
            }
            break;

        default:

            break;
        }

        printf("current state: %d , current floor: %d , current direction: %d\n", elev->state, elev->current_floor + 1, elev->current_direction);


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
        }*/


        if(elevio_obstruction()){
            elevio_stopLamp(0);      
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

