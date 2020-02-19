
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "timer.h"

int timer_length;

void setTimerLength(int millisecs){
    timer_length = millisecs;
}


int startTimer(){
    int time_passed = 0;
    clock_t start_time = clock();

    do {
        clock_t time_diff = clock() - start_time;
        time_passed = time_diff * 1000 / CLOCKS_PER_SEC;
    } while (time_passed < timer_length);
    
    return 1;
};
