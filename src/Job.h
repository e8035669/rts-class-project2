#pragma once

#include "Task.h"

struct Job {
    int release_time;
    int remain_execution_time;
    int absolute_deadline;
    const Task& parent_task;
};
