#include "Simulator.h"

#include <iostream>
#include "Job.h"

using namespace std;

Simulator::Simulator()
    : clock_(0),
      max_clock_(0),
      periodic_tasks_(),
      aperiodic_tasks_(),
      periodic_jobs_(),
      aperiodic_jobs_(),
      total_response_time_(0),
      finished_ajob_number_(0),
      miss_pjob_number_(0),
      total_pjob_number_(0) {}

void Simulator::assign_ptasks(const std::vector<Task>& periodic_tasks) {
    periodic_tasks_ = periodic_tasks;
}

void Simulator::assign_atasks(const AperiodicTasks& aperiodic_tasks) {
    aperiodic_tasks_ = aperiodic_tasks;
}

bool Simulator::run_once() {
    if (clock_ < max_clock_) {
        remove_miss_job();

        //
        clock_++;
        if (clock_ < max_clock_) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void Simulator::remove_miss_job() {
    for (auto it = periodic_jobs_.begin(); it != periodic_jobs_.end();) {
        if ((it->absolute_deadline - clock_ - it->remain_execution_time) < 0) {
            cout << "Miss Periodic Job: T" << it->parent_task.task_id << endl;
            miss_pjob_number_++;
            it = periodic_jobs_.erase(it);
        } else {
            ++it;
        }
    }
}

void Simulator::add_periodic_job() {
    for (Task& task : periodic_tasks_) {
        if ((clock_ % task.period) == 0) {
            Job job {
                .release_time = clock_,
                .remain_execution_time = task.execution_time,
                .absolute_deadline = clock_ + task.period,
                .parent_task = task,
            };
            periodic_jobs_.push_back(job);
            total_pjob_number_++;
        }

    }

}



