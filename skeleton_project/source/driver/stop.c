#include "stop.h"
#include <time.h>

void STOP_status(elevator * elev){
    if(elevio_stopButton() == 1){
        elev->state = STOP;
    }
}

void STOP_doors(elevator * elev){
    if(elev->between_floors == 0){
        while (elevio_stopButton() == 1)
        {
            elevio_doorOpenLamp(1);
        }
        nanosleep(&(struct timespec){3 ,0}, NULL);
        elevio_doorOpenLamp(0);
    }
}