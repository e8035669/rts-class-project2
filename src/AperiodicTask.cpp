#include "AperiodicTask.h"

#include <string>

AperiodicTask::AperiodicTask() {}

AperiodicTask::AperiodicTask(int task_id, int phase, int execution_time)
    : task_id(task_id), phase(phase), execution_time(execution_time) {
    //
}

std::string AperiodicTask::to_string() const {
    //
    return "A" + std::to_string(task_id) + ": (" + std::to_string(phase) +
           ", " + std::to_string(execution_time) + ")";
}
