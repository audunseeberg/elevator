/**
 * @file
 * 
 * @brief Timer functionality.
 * 
 */

/**
 * @brief Sets the duration of the timer.
 * 
 * @param time_in_ms Timer duration in milliseconds.
 */
void set_timer_duration(int time_in_ms);

/**
 * @brief Starts the timer and lets it run for the set timer duration unless the
 * obstruction button is pushed. Runs stop-procedure if stop button is pushed during.
 * 
 * @return 0 if the obstruction button is pushed. 1 otherwise (after timer_duration milliseconds).
 */
int start_timer();