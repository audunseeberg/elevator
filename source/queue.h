/**
 * @file
 * @brief Implements queue system for orders.
 */
#include <stdbool.h>
#include "hardware.h"


/**
 * @brief Encodes order to corresponding int.
 * 
 * @param floor Floor to be encoded.
 * @param type Order type to be encoded.
 * @return Order as an integer.
 */
int order_to_int_encoding(int floor, HardwareOrder type);

/**
 * @brief Adds an order to the queue, @p orders.
 * 
 * @param floor Floor to add.
 * @param type Order type to add.
 * @param orders Pointer to queue.
 * @param array_size Size of queue array.
 */
void add_order(int floor, HardwareOrder type, int (*orders)[10], int array_size);

/**
 * @brief Deletes all orders on specified @p floor from the queue, @p orders, then restacks the queue.
 * 
 * @param floor Floor to delete orders on.
 * @param orders Pointer to queue.
 * @param array_size Size of queue array.
 */
void del_all_orders_on_floor(int floor, int (*orders)[10], int array_size);

/**
 * @brief Deletes all orders in queue, @p orders.
 * 
 * @param orders Pointer to queue.
 * @param array_size Size of queue array. 
 */
void del_all_orders(int (*orders)[10], int array_size);

/**
 * @brief Checks if a specified order is in the queue, @p orders.
 * 
 * @param floor Floor to look for.
 * @param type Order type to look for.
 * @param orders Pointer to queue.
 * @param array_size Size of queue array.
 * @return 1 if order in queue. 0 otherwise.
 */
bool check_queue_for_order(int floor, HardwareOrder type, int (*orders)[10], int array_size);



/**
 * @brief Checks if there are orders in the queue, @p orders, requiring the elevator to stop.
 * 
 * @param floor Current elevator floor.
 * @param direction Current elevator direction.
 * @param orders Pointer to queue.
 * @param array_size Size of queue array.
 * @return 1 if elevator should stop. 0 otherwise.
 */
bool check_for_stop(int floor, HardwareMovement direction, int (*orders)[10], int array_size);


/**
 * @brief Checks if the queue, @p orders, has any valid orders.
 * 
 * @param orders Pointer to queue.
 * @return 1 if queue empty. 0 otherwise.
 */
bool check_if_queue_empty(int (*orders)[10]);
