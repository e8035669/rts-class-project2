#pragma once

#include <string>

struct AperiodicTask {
    AperiodicTask();
    AperiodicTask(int task_id, int phase, int execution_time);

    int task_id;
    int phase;
    int execution_time;

    std::string to_string() const;
};
