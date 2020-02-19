#include "hardware.h"

void add_order(int floor, HardwareOrder type);

void del_all_orders_on_floor(int floor);

bool check_queue_for_order(int floor, HardwareOrder type);

bool check_for_stop(int floor, HardwareMovement direction);

int check_queue_length();
