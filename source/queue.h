/**
 * @file
 * @brief Implements queue system for orders
 */
#include "hardware.h"

/**
 * @brief Encodes order to corresponding int
 * 
 * @param floor Floor to be encoded
 * @param type Order type to be encoded
 * @return Order as an integer.
 */
int order_to_int_encoding(int floor, HardwareOrder type);

/**
 * @brief Adds an order to the queue
 * 
 * @param floor Floor to add
 * @param type Order type to add
 */
void add_order(int floor, HardwareOrder type);

/**
 * @brief Deletes all orders in the queue on specified floor.
 * 
 * @param floor Floor to delete orders on.
 */
void del_all_orders_on_floor(int floor);

/**
 * @brief Checks if a specified order is in the queue.
 * 
 * @param floor Floor to look for
 * @param type Order type to look for
 * @return 1 if order in queue. 0 otherwise 
 */
bool check_queue_for_order(int floor, HardwareOrder type);



/**
 * @brief Checks if there are orders in the queue requiring the elevator to stop.
 * 
 * @param floor Current elevator floor
 * @param direction Current elevator direction
 * @return 1 if elevator should stop. 0 otherwise.
 */
bool check_for_stop(int floor, HardwareMovement direction);


/**
 * @brief Checks if the queue has any valid orders
 * 
 * @return 1 if queue empty. 0 otherwise.
 */
bool check_if_queue_empty();
