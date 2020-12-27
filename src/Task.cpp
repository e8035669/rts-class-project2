#include "Task.h"

#include <algorithm>
#include <string>

Task::Task() {
    //
}

Task::Task(int task_id, int period, int execution_time)
    : task_id(task_id), period(period) {
    //
}

double Task::utilization() const {
    if (period != 0) {
        return (double)execution_time / period;
    }
    return 0;
}

std::string Task::to_string() const {
    return "T" + std::to_string(task_id) + ": (" + std::to_string(period) +
           ", " + std::to_string(execution_time) + ")";
}
