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

void poll_orders_and_add_to_queue() {
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            if(hardware_read_order(f, type) && !check_queue_for_order(f, type)){
                add_order(f, type);
            }
        }
    }
}