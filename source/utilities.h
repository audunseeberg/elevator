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

/**
 * @brief Polls order buttons and adds order to queue, @p orders, if button pressed.
 * 
 * @param orders Pointer to queue.
 * @param array_size Size of queue array.
 */
void poll_orders_and_add_to_queue(int (*orders)[10], int array_size);

/**
 * @brief Sets all order lights to 0 (off).
 * 
 */
void clear_all_order_lights();

/**
 * @brief State types used in the FSM in @c main.
 * 
 */
typedef enum {
    GOING_UP,
    IDLE,
    GOING_DOWN,
    ORDER_EXPEDITION
} states;

/**
 * @brief Initializes elevator to a known state.
 * 
 * @return Current state.
 */
states elevator_init();