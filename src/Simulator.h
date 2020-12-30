#pragma once

#include <vector>
#include <list>

#include "AperiodicJob.h"
#include "AperiodicTasks.h"
#include "Job.h"
#include "Task.h"

class Simulator {
   public:
    enum Mode { CUS, TBS };

   private:
    int clock_;
    int max_clock_;

    std::vector<Task> periodic_tasks_;
    AperiodicTasks aperiodic_tasks_;

    std::list<Job> periodic_jobs_;
    Mode aperiodic_server_mode_;
    std::list<AperiodicJob> aperiodic_jobs_;
    double server_size_;
    int cus_deadline_;
    int budget_;

    int total_response_time_;
    int finished_ajob_number_;
    int miss_pjob_number_;
    int total_pjob_number_;

   public:
    Simulator();

    void set_max_clock(int max_clock) { max_clock_ = max_clock; }

    void set_server_size(double server_size) { server_size_ = server_size; }

    void set_aperiodic_server_mode(Mode aperiodic_server_mode) {
        aperiodic_server_mode_ = aperiodic_server_mode;
    }

    void assign_ptasks(const std::vector<Task>& periodic_tasks);

    void assign_atasks(const AperiodicTasks& aperiodic_tasks);

    bool run_once();

    void remove_miss_job();

    void add_periodic_job();

    void add_aperiodic_job();

    void doing_job();

    void clean_periodic_job();

    void clean_aperiodic_job();

    void print_statistics();
};
