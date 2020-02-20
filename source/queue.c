#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
int orders[10];

int orders[10] = {-1};
int array_size = (sizeof(orders)/sizeof(orders[0]));

int order_to_int_encoding(int floor, HardwareOrder type){
    return (floor-1)*3+(int)type;
}

void add_order(int floor, HardwareOrder type){
	for (int i = 9;i > -1;i--) {
		if (orders[i] != -1) {
			orders[i + 1] = (((floor-1) * 3) + (int)type);
		}
	}

}

void del_all_orders_on_floor(int floor){
    for (int i = 0; i < sizeof(orders); i++){
        for (int j = 0; j < 3; j++){
            if (orders[i] = order_to_int_encoding(floor, j)){
                orders[i] = -1;
            }
        }
    }
    int next_in_queue = 0;                                          //restacks the queue to place valid orders first
    int array_size = (sizeof(orders)/sizeof(orders[0]));
    for (int c = 0; c < array_size; c++){
        if (orders[c] != -1){
            orders[next_in_queue++] = orders[c];
        }  
    }
    while (next_in_queue < array_size) {
        orders[next_in_queue++] = -1;
    }
}

bool check_queue_for_order(int floor, HardwareOrder type){
    int order_int = order_to_int_encoding(floor, type);
    for (int i = 0;i < 10;i++) {
        if (orders[i] == order_int) {
            return 1;
        }
    }

}

bool check_for_stop(int floor, HardwareMovement direction){
    if (check_queue_for_order(floor, direction) || check_queue_for_order(floor, 1)){
        return 1;
    }
}

bool check_if_queue_empty(){
    return orders[0] == -1 ? 1 : 0;
}
