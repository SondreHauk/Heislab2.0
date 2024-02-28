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
    elev->current_direction = 0;
    elev->next_stop = 0;
    elev->temporary_stop = 0;
    elev->STOP = 0;
    elev->door = 0;
    elev->state = INIT;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            elev->buttons[i][j] = 0;
        }
    }
    return elev;
}

void update_direction(elevator * elev){
    int STOP = elev->STOP;
    int current_floor = elev->current_floor;
    int next_stop = elev->next_stop;
    MotorDirection old_direction = elev->current_direction;
    elev->current_direction = update_current_direction(STOP, old_direction, current_floor, next_stop);
}

/*Denne funksjonen oppdaterer prev_floor til å være current_floor og 
current_floor til å være den nye etasjen heisen er i.*/
void update_floors(elevator * elev){
    if (elevio_floorSensor() != -1){
    elev->prev_floor = elev->current_floor;
    elev->current_floor = elevio_floorSensor();
    elev->between_floors = 0;
    }
    else{
        elev->between_floors = 1;
    }
}