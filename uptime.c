#include <time.h>

time_t start_time, current_time;

// Set start time for the uptime command
void set_uptime_start() {
    start_time = time(NULL);
}

// Returns program uptime in seconds as a double value
int get_uptime() {
    current_time = time(NULL);
    double interval = difftime(current_time, start_time);
    return (int)interval;
}
