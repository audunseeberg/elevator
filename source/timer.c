
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "timer.h"
#include "hardware.h"
#include "utilities.h"
#include "queue.h"

int timer_duration;

void set_timer_duration(int time_in_ms){
    timer_duration = time_in_ms;
}


int start_timer(int (*orders)[10], int array_size){
    int time_passed = 0;
    clock_t start_time = clock();
    do {
        clock_t time_diff = clock() - start_time;
        time_passed = time_diff * 1000 / CLOCKS_PER_SEC;
        if (hardware_read_stop_signal()){
            return 1;
        }
        if (hardware_read_obstruction_signal()){
            poll_orders_and_add_to_queue(orders, array_size);
            return 1;
        }
        poll_orders_and_add_to_queue(orders, array_size);
        hardware_command_stop_light(0);
    } while (time_passed < timer_duration);
    return 0;
};
