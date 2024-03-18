#include "doors.h"
#include <time.h>


void open_doors(elevator * elev){
    /*if(elevio_floorSensor() == -1){
        elev->state = MOVING;
    }
    else{
        reset_current_floor_buttons(elev);
        elevio_doorOpenLamp(1);
    }*/
    if(elevio_floorSensor() != -1){
        reset_current_floor_buttons(elev);
        elevio_doorOpenLamp(1);
        /*while (elevio_obstruction() == 1)
        {
            elevio_doorOpenLamp(1);
        }*/
        for(int i = 0; i < 30; i++){
            nanosleep(&(struct timespec){0, 1000*1000*100}, NULL);
            updateAllButtons(elev);
            if(elevio_stopButton() == 1){
                elev->state = STOP;
            }
            while(elevio_obstruction() == 1){
                updateAllButtons(elev);
            }
        }
        
        elevio_doorOpenLamp(0);
    }
}

