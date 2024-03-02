#include "stop.h"

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
        delay(3000);
        elevio_doorOpenLamp(0);
    }
}