#pragma once

#include <vector>

#include "AperiodicTasks.h"
#include "Task.h"

class Simulator {
   private:
    int clock_;
    int max_clock_;

    std::vector<Task> periodic_tasks_;
    AperiodicTasks aperiodic_tasks_;

    int total_response_time_;
    int finished_ajob_number_;
    int miss_pjob_number_;
    int total_pjob_number_;

   public:
    Simulator();

    void set_max_clock(int max_clock) { max_clock_ = max_clock; }

    bool run_once();
};
