#include <stdio.h>
#include "hardware.h"

int read_current_floor_and_set_floor_light() {
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS-1; i++){
        if(hardware_read_floor_sensor(i)){
            hardware_command_floor_indicator_on(i);
            return i+1;
        }
        else {
            return 0;
        }
        
    }
}
