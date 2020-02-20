#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
int orders[10];

void add_order(int floor, HardwareOrder type){
	for (int i = 9;i > -1;i--) {
		if (orders[i] != -1) {
			orders[i + 1] = (((floor-1) * 3) + (int)type);
		}
	}

}

void del_all_orders_on_floor(int floor){
	for (int i = 0;i < 10;i++) {
		if (orders[i] >= ((floor - 1) * 3) || (orders[i] < (((floor - 1) * 3) + 3))) {
			orders[i] = (-1);
		}
	}

}

int check_queue_for_order(int floor, HardwareOrder type){

}

bool check_for_stop(int floor, HardwareMovement direction){

}

int check_queue_length(){

}
