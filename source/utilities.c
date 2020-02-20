#include <stdio.h>
#include <stdbool.h>
#include "hardware.h"
#include "queue.h"
#include "utilities.h"


int read_current_floor_and_set_floor_light() {
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            hardware_command_floor_indicator_on(i);
            return i+1;
        }
    }
    return 0;
}

void poll_orders_and_add_to_queue(int* orders, int array_size) {
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            if(hardware_read_order(f, i) && !check_queue_for_order(f, i, orders)){
                add_order(f, i, orders, array_size);
                hardware_command_order_light(f, i, 1);
            }
        }
    }
}

void clear_all_order_lights(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            hardware_command_order_light(f, i, 0);
        }
    }
}

states elevator_init(){
    while (!read_current_floor_and_set_floor_light()){
        hardware_command_movement(HARDWARE_ORDER_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    return IDLE;
}