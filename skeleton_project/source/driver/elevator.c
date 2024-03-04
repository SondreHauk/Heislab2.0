#include "elevator.h"
#include "direction_control.h"
#include "elevio.h"
#include "button.h"
//Kode generert av GitHub Copilot
elevator * elevator_setup_maker(){
    elevator * elev = malloc(sizeof(elevator));
    elev->current_floor = elevio_floorSensor();
    elev->prev_floor = elev->current_floor; //Må holde styr på previous floor!
    elev->between_floors = 0;
    elev->current_direction = DIRN_STOP;
    elev->prev_direction = DIRN_STOP;
    elev->next_stop = 0;
    elev->temporary_stop = 0;
    elev->STOP = 0;
    elev->door = 0;
    elev->state = INIT;
    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
            elev->buttons[i][j] = 0;
        }
    }
    return elev;
}
/*Denne funksjonen oppdaterer current direction i elev, 
og setter den fysisk med elevio*/
void update_direction(elevator * elev){
    elev->prev_direction = elev->current_direction;
    elev->current_direction = update_current_direction(elev->current_floor, elev->next_stop);
    elevio_motorDirection(elev->current_direction);
}

/*Denne funksjonen oppdaterer prev_floor til å være current_floor og 
current_floor til å være den nye etasjen heisen er i.*/
void update_floors(elevator * elev){
    if (elevio_floorSensor() != -1){
    elev->prev_floor = elev->current_floor;
    elev->current_floor = elevio_floorSensor();
    elev->between_floors = 0;
    elevio_floorIndicator(elev->current_floor);
    }
    else{
        elev->between_floors = 1;
    }
}