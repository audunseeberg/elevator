
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "timer.h"

int timer_duration;

void set_timer_duration(int time_in_ms){
    timer_duration = time_in_ms;
}


int startTimer(){
    int time_passed = 0;
    clock_t start_time = clock();
    bool stop_active = 0;

    do {
        clock_t time_diff = clock() - start_time;
        time_passed = time_diff * 1000 / CLOCKS_PER_SEC;
        if(hardware_read_stop_sigal()){
            stop_active = 1;
        }
        if (hardware_obstruction_signal()){
            return 0;
        }

    } while (time_passed < timer_duration);
    
    if (stop_active){
        stop_procedure();
    }

    return 0;
};
