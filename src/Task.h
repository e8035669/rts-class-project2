#pragma once

#include <string>
struct Task {
    Task();

    Task(int task_id, int period, int execution_time);

    int task_id;
    int period;
    int execution_time;

    double utilization() const;

    std::string to_string() const;
};
