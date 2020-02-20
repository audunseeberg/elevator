/**
 * @file
 * @brief Various utilities to simplify interaction with hardware.
 * 
 */

/**
 * @brief Checks if any of the floor sensors are active, and sets the corresponding
 * floor light if it is.
 * 
 * @return Floor number if floor sensor active. 0 otherwise.
 */
int read_current_floor_and_set_floor_light();

void poll_orders_and_add_to_queue();

void clear_all_order_lights();

typedef enum {
    GOING_UP,
    IDLE,
    GOING_DOWN,
    ORDER_EXPEDITION
} states;

/**
 * @brief Initializes elevator to a known state.
 * 
 * @return Current state 
 */
states elevator_init();