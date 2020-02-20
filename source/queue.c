#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

int orders[10] = {-1};

int order_to_int_encoding(int floor, HardwareOrder type){
    return (floor-1)*3+(int)type;
}

void add_order(int floor, HardwareOrder type){

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

}

bool check_for_stop(int floor, HardwareMovement direction){

}

bool check_if_queue_empty(){

}

int main(){
    int o[10] = {0, 8, 5, 6, 4, -1, 3, 7, -1, 10};
    int next_in_queue = 0;
    int array_size = (sizeof(o)/sizeof(o[0]));
    for (int c = 0; c < array_size; c++){
        if (o[c] != -1){
            o[next_in_queue++] = o[c];
        }  
    }
    while (next_in_queue < array_size) {
        o[next_in_queue++] = -1;
    }
}
