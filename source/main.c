#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "utilities.h"
#include "queue.h"
#include "timer.h"


static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);


    int orders[10] = { [0 ... 9] =-1 };
    int array_size = (sizeof(orders)/sizeof(orders[0]));

    states current_state = elevator_init(); 
    
    int current_floor = read_current_floor_and_set_floor_light()-1; 

    int door_state = 0;

    int target_floor;

    int current_dir;

    set_timer_duration(3000);

     while(1){

        switch (current_state)
        {
        case IDLE:
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            if (hardware_read_stop_signal()){
                del_all_orders(&orders, array_size);
                clear_all_order_lights();
                hardware_command_stop_light(1);
                if (read_current_floor_and_set_floor_light()){
                    hardware_command_door_open(1);
                    door_state = start_timer(&orders, array_size);
                    hardware_command_door_open(door_state);
                    break;
                }
                break;
            }
            hardware_command_stop_light(0);
            if (door_state){
                current_state = ORDER_EXPEDITION;
                break;
            }

            poll_orders_and_add_to_queue(&orders, array_size);
            
            if (!check_if_queue_empty(&orders)){
                target_floor = (orders[0]/3);
                if (target_floor > current_floor){
                    current_state = GOING_UP;
                    break;
                }

                if (target_floor < current_floor){
                    current_state = GOING_DOWN;
                    break;
                }
                if (target_floor == current_floor && read_current_floor_and_set_floor_light()){
                    current_state = ORDER_EXPEDITION;
                    break;
                }    
                if (target_floor == current_floor && !read_current_floor_and_set_floor_light()){
                    if (current_dir == HARDWARE_MOVEMENT_DOWN){
                        current_state = GOING_UP;
                    }
                    if (current_dir == HARDWARE_MOVEMENT_UP){
                        current_state = GOING_DOWN;
                    }
                }
            }

            break;

        case GOING_UP:
            if (hardware_read_stop_signal()){
                del_all_orders(&orders, array_size);
                clear_all_order_lights();
                hardware_command_stop_light(1);
                current_state = IDLE;
                break;
            }
            current_dir = HARDWARE_MOVEMENT_UP;
            hardware_command_movement(current_dir);
            poll_orders_and_add_to_queue(&orders, array_size);
            int curr_floor_buffer_up = read_current_floor_and_set_floor_light();
            if (curr_floor_buffer_up){
                current_floor = curr_floor_buffer_up-1;
                if(check_for_stop(current_floor, HARDWARE_MOVEMENT_UP, &orders, array_size) || current_floor == target_floor){
                    current_state = ORDER_EXPEDITION;
                    break;
                }
            }
            break;
        
        case GOING_DOWN:
            if (hardware_read_stop_signal()){
                del_all_orders(&orders, array_size);
                clear_all_order_lights();
                hardware_command_stop_light(1);
                current_state = IDLE;
                break;
            }
            current_dir = HARDWARE_ORDER_DOWN;
            hardware_command_movement(current_dir);
            poll_orders_and_add_to_queue(&orders, array_size);
            int curr_floor_buffer_down = read_current_floor_and_set_floor_light();
            if (curr_floor_buffer_down){
                current_floor = curr_floor_buffer_down-1;
                if(check_for_stop(current_floor, HARDWARE_MOVEMENT_DOWN, &orders, array_size) || current_floor == target_floor){
                    current_state = ORDER_EXPEDITION;
                    break;
                }
            }
            break;
        
        case ORDER_EXPEDITION:
            if (hardware_read_stop_signal()){
                del_all_orders(&orders, array_size);
                clear_all_order_lights();
                hardware_command_stop_light(1);
                current_state = IDLE;
                break;
            }
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            door_state = 1;
            hardware_command_door_open(door_state);
            door_state = start_timer(&orders, array_size);
            del_all_orders_on_floor(current_floor, &orders, array_size);
            hardware_command_door_open(door_state);
            if (door_state){
                break;
            }
            if (!check_if_queue_empty(&orders)){
                target_floor = (orders[0]/3);
                if (target_floor > current_floor){
                    current_state = GOING_UP;
                        break;
                }

                if (target_floor < current_floor){
                    current_state = GOING_DOWN;
                    break;
                }
            }
            current_state = IDLE;
            break;    
        
        default:
            current_state = elevator_init();
            del_all_orders(&orders, array_size);
            clear_all_order_lights();
            break;
        }
    }   
    return 0;
}

