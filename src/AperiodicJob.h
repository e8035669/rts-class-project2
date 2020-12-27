#pragma once

#include "AperiodicTask.h"

struct AperiodicJob {
    int remain_execution_time;
    const AperiodicTask& parent_task;
};





