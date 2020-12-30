#pragma once

#include <vector>

#include "AperiodicJob.h"
#include "AperiodicTasks.h"
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
    double server_size_;
    int cus_deadline_;

    int total_response_time_;
    int finished_ajob_number_;
    int miss_pjob_number_;
    int total_pjob_number_;

   public:
    Simulator();

    void set_max_clock(int max_clock) { max_clock_ = max_clock; }

    void set_server_size(double server_size) { server_size_ = server_size; }

    void assign_ptasks(const std::vector<Task>& periodic_tasks);

    void assign_atasks(const AperiodicTasks& aperiodic_tasks);

    bool run_once();

    void remove_miss_job();

    void add_periodic_job();

    void add_aperiodic_job();

    void doing_job();
};
