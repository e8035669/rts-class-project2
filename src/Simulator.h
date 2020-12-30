#pragma once

#include <vector>

#include "AperiodicTasks.h"
#include "AperiodicJob.h"
#include "Job.h"
#include "Task.h"

class Simulator {
   private:
    int clock_;
    int max_clock_;

    std::vector<Task> periodic_tasks_;
    AperiodicTasks aperiodic_tasks_;

    std::vector<Job> periodic_jobs_;
    std::vector<AperiodicJob> aperiodic_jobs_;

    int total_response_time_;
    int finished_ajob_number_;
    int miss_pjob_number_;
    int total_pjob_number_;

   public:
    Simulator();

    void set_max_clock(int max_clock) { max_clock_ = max_clock; }

    void assign_ptasks(const std::vector<Task>& periodic_tasks);

    void assign_atasks(const AperiodicTasks& aperiodic_tasks);

    bool run_once();

    void remove_miss_job();

    void add_periodic_job();




};
