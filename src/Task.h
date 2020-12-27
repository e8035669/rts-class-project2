#pragma once

#include <string>
struct Task {
    Task();

    Task(int task_id, int phase, int period, int relative_deadline,
         int execution_time);

    int task_id;
    int phase;
    int period;
    int relative_deadline;
    int execution_time;

    double utilization() const;

    std::string ToString() const;
};
