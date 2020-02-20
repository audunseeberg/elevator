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
    
    int current_floor = read_current_floor_and_set_floor_light; 

    int door_state = 0;


    while(1){

        switch (current_state)
        {
        case IDLE:
            if (hardware_read_stop_signal()){
                del_all_orders();
                clear_all_order_lights();
                hardware_command_stop_light(1);
                if (read_current_floor_and_set_floor_light()){
                    hardware_command_door_open(1);
                    door_state = start_timer(&orders, array_size );
                    hardware_command_door_open(door_state);
                    break;
                }
                break;
            }
            if (door_state){
                current_state = ORDER_EXPEDITION;
                break;
            }

            poll_orders_and_add_to_queue(&orders, array_size);
            
            if (!check_if_queue_empty(&orders)){
                int target_floor = (orders[0]/3)+1;
                if (target_floor > current_floor){
                    current_state = GOING_UP;
                    break;
                }

                if (target_floor < current_floor){
                    current_state = GOING_DOWN;
                    break;
                }
                if (target_floor == current_floor){
                    current_state = ORDER_EXPEDITION;
                    break;
                }    
            }

            break;

        case GOING_UP:
            if (hardware_read_stop_signal()){
                del_all_orders();
                clear_all_order_lights();
                hardware_command_stop_light(1);
                current_state = IDLE;
                break;
            }
            break;
        
        case GOING_DOWN:
            if (hardware_read_stop_signal()){
                del_all_orders();
                clear_all_order_lights();
                hardware_command_stop_light(1);
                current_state = IDLE;
                break;
            }
            break;
        
        case ORDER_EXPEDITION:
            if (hardware_read_stop_signal()){
                del_all_orders();
                clear_all_order_lights();
                hardware_command_stop_light(1);
                current_state = IDLE;
                break;
            }
            door_state = 1;
            hardware_command_door_open(door_state);
            del_all_orders_on_floor(current_floor, orders, array_size);
            door_state = start_timer(&orders, array_size );
            hardware_command_door_open(door_state);
            if (door_state){
                break;
            }
            if (!check_if_queue_empty(&orders)){
                int target_floor = (orders[0]/3)+1;
                if (target_floor > current_floor){
                    current_state = GOING_UP;
                        break;
                }

                if (target_floor < current_floor){
                    current_state = GOING_DOWN;
                    break;
                }
            current_state = IDLE;
            break;    
        
        default:
            current_state = elevator_init();
            break;
        }
    }
    // printf("=== Example Program ===\n");
    // printf("Press the stop button on the elevator panel to exit\n");

    // hardware_command_movement(HARDWARE_MOVEMENT_UP);

    // while(1){
    //     if(hardware_read_stop_signal()){
    //         hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    //         break;
    //     }

    //     if(hardware_read_floor_sensor(0)){
    //         hardware_command_movement(HARDWARE_MOVEMENT_UP);
    //     }
    //     if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
    //         hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    //     }

    //     /* All buttons must be polled, like this: */
    //     for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
    //         if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
    //             hardware_command_floor_indicator_on(f);
    //         }
    //     }

    //     /* Lights are set and cleared like this: */
    //     for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
    //         /* Internal orders */
    //         if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
    //             hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
    //         }

    //         /* Orders going up */
    //         if(hardware_read_order(f, HARDWARE_ORDER_UP)){
    //             hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
    //         }

    //         /* Orders going down */
    //         if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
    //             hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
    //         }
    //     }

    //     if(hardware_read_obstruction_signal()){
    //         hardware_command_stop_light(1);
    //         clear_all_order_lights();
    //     }
    //     else{
    //         hardware_command_stop_light(0);
    //     }
    // }

    return 0;
}
