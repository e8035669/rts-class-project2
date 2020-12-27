#include "Task.h"

#include <algorithm>
#include <string>

Task::Task() {
    //
}

Task::Task(int task_id, int phase, int period, int relative_deadline,
           int execution_time)
    : task_id(task_id),
      phase(phase),
      period(period),
      relative_deadline(relative_deadline) {
    //
}

double Task::utilization() const {
    if (std::min(period, relative_deadline) != 0) {
        return (double)execution_time / std::min(period, relative_deadline);
    }
    return 0;
}

std::string Task::ToString() const {
    return "T" + std::to_string(task_id) + ": (" + std::to_string(phase) +
           ", " + std::to_string(period) + ", " +
           std::to_string(relative_deadline) + ", " +
           std::to_string(execution_time) + ")";
}
