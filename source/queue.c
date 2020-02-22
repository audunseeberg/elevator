#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
#include "hardware.h"



int order_to_int_encoding(int floor, HardwareOrder type){
    return (floor)*3+(int)type;
}

void add_order(int floor, HardwareOrder type, int (*orders)[10], int array_size){
    if (!check_queue_for_order(floor, type, orders, array_size)) {
        for (int i = 0; i < array_size; i++) {
            if (*(*orders+i) == -1){
			    *(*orders+i) = order_to_int_encoding(floor, type);
                break;
            }
        }
	}
}


void del_all_orders_on_floor(int floor, int (*orders)[10], int array_size){
    for (int i = 0; i < array_size; i++){
        for (int j = 0; j < 3; j++){
            if ((*(*orders+i) == order_to_int_encoding(floor, j))){
                *(*orders+i) = -1;
            }
            hardware_command_order_light(floor, j, 0);
        }
    }
    int next_in_queue = 0;                                          //restacks the queue to place valid *orders first
    for (int c = 0; c < array_size; c++){
        if (*(*orders+c) != -1){
            *(*orders+next_in_queue) = *(*orders+c);
            next_in_queue++;
        }  
    }
    while (next_in_queue < array_size) {
        *(*orders+next_in_queue) = -1;
        next_in_queue++;
    }
}

void del_all_orders(int (*orders)[10], int array_size){
    for (int i = 0; i < array_size; i++){
        *(*orders+i) = -1;
    }
}


bool check_queue_for_order(int floor, HardwareOrder type, int (*orders)[10], int array_size){
    int order_int = order_to_int_encoding(floor, type);
    for (int i = 0; i < array_size ; i++) {
        if (*(*orders+i) == order_int) {
            return 1;
        }
    }
    return 0;
}

bool check_for_stop(int floor, HardwareMovement direction, int (*orders)[10], int array_size){
    if (check_queue_for_order(floor, direction, orders, array_size)  || check_queue_for_order(floor, 1, orders, array_size)){
        return 1;
    }
    return 0;
}

bool check_if_queue_empty(int (*orders)[10]){
    return *(*orders+0) == -1 ? 1 : 0;
}