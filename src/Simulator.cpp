#include "Simulator.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

#include "AperiodicJob.h"
#include "AperiodicTask.h"
#include "Job.h"

using namespace std;

Simulator::Simulator()
    : clock_(0),
      max_clock_(0),
      periodic_tasks_(),
      aperiodic_server_mode_(Mode::CUS),
      aperiodic_tasks_(),
      periodic_jobs_(),
      aperiodic_jobs_(),
      server_size_(0.2),
      cus_deadline_(0),
      budget_(0),
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
        add_periodic_job();
        add_aperiodic_job();
        doing_job();
        clean_periodic_job();
        clean_aperiodic_job();

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
            Job job{
                .release_time = clock_,
                .remain_execution_time = task.execution_time,
                .absolute_deadline = clock_ + task.period,
                .parent_task = task,
            };

            auto it = find_if(
                periodic_jobs_.begin(), periodic_jobs_.end(), [&job](Job& j) {
                    return job.absolute_deadline < j.absolute_deadline;
                });
            periodic_jobs_.insert(it, job);
            total_pjob_number_++;
        }
    }
}

void Simulator::add_aperiodic_job() {
    auto atasks = aperiodic_tasks_.getAperiodicTask(clock_);
    for (AperiodicTask* atask : atasks) {
        if (atask->phase == clock_) {
            AperiodicJob job{.remain_execution_time = atask->execution_time,
                             .parent_task = *atask};

            if (aperiodic_jobs_.size() == 0) {
                if (aperiodic_server_mode_ == Mode::CUS) {
                    if (clock_ < cus_deadline_) {
                        // Do nothing.
                    } else {
                        cus_deadline_ = (int)round(
                            clock_ + atask->execution_time / server_size_);
                        budget_ = atask->execution_time;
                        cout << "CUS DL: " << cus_deadline_
                             << ", budget: " << budget_ << endl;
                    }

                } else {
                    cus_deadline_ =
                        (int)round(max(clock_, cus_deadline_) +
                                   atask->execution_time / server_size_);
                    budget_ = atask->execution_time;
                    cout << "TBS DL: " << cus_deadline_
                         << ", budget: " << budget_ << endl;
                }
            }
            aperiodic_jobs_.push_back(job);
        }
    }

    if (aperiodic_server_mode_ == Mode::CUS) {
        if (budget_ == 0 && clock_ >= cus_deadline_ &&
            aperiodic_jobs_.size() > 0) {
            cus_deadline_ = (int)round(
                clock_ + aperiodic_jobs_.front().parent_task.execution_time /
                             server_size_);
            budget_ = aperiodic_jobs_.front().parent_task.execution_time;
            cout << "CUS DL: " << cus_deadline_ << ", budget: " << budget_
                 << endl;
        }
    } else {
        if (budget_ == 0 && aperiodic_jobs_.size() > 0) {
            cus_deadline_ =
                (int)round(cus_deadline_ +
                           (aperiodic_jobs_.front().parent_task.execution_time /
                            server_size_));
            budget_ = aperiodic_jobs_.front().remain_execution_time;
            cout << "TBS DL: " << cus_deadline_ << ", budget: " << budget_
                 << endl;
        }
    }
}

void Simulator::doing_job() {
    int pjob_deadline = numeric_limits<int>::max();
    if (periodic_jobs_.size() > 0) {
        pjob_deadline = periodic_jobs_.front().absolute_deadline;
    }

    if (pjob_deadline != numeric_limits<int>::max() &&
        (pjob_deadline <= cus_deadline_ || budget_ == 0)) {
        periodic_jobs_.front().remain_execution_time--;
        cout << "Time: " << clock_ << ", T"
             << periodic_jobs_.front().parent_task.task_id << endl;
    } else if (cus_deadline_ != numeric_limits<int>::max() &&
               cus_deadline_ < pjob_deadline && budget_ > 0) {
        aperiodic_jobs_.front().remain_execution_time--;
        budget_--;
        cout << "Time: " << clock_ << ", A"
             << aperiodic_jobs_.front().parent_task.task_id << endl;
    } else {
        cout << "Time: " << clock_ << ", Nothing to do" << endl;
    }
}

void Simulator::clean_periodic_job() {
    if (periodic_jobs_.size() > 0 &&
        periodic_jobs_.front().remain_execution_time == 0) {
        periodic_jobs_.erase(periodic_jobs_.begin());
    }
}

void Simulator::clean_aperiodic_job() {
    if (aperiodic_jobs_.size() > 0 &&
        aperiodic_jobs_.front().remain_execution_time == 0) {
        finished_ajob_number_++;
        total_response_time_ +=
            (clock_ - aperiodic_jobs_.front().parent_task.phase);
        aperiodic_jobs_.erase(aperiodic_jobs_.begin());
    }

    /*
    if (aperiodic_server_mode_ == CUS) {
        if (clock_ >= cus_deadline_ && aperiodic_jobs_.size() > 0) {
            cus_deadline_ = (int)round(
                clock_ + (aperiodic_jobs_.front().parent_task.execution_time /
                          server_size_));
            budget_ = aperiodic_jobs_.front().remain_execution_time;
            cout << "CUS DL: " << cus_deadline_ << ", budget: " << budget_
                 << endl;
        }
    } else {
        if (budget_ == 0 && aperiodic_jobs_.size() > 0) {
            cus_deadline_ =
                (int)round(cus_deadline_ +
                           (aperiodic_jobs_.front().parent_task.execution_time /
                            server_size_));
            budget_ = aperiodic_jobs_.front().remain_execution_time;
            cout << "TBS DL: " << cus_deadline_ << ", budget: " << budget_
                 << endl;
        }
    }
    */
}

void Simulator::print_statistics() {
    double miss_rate = (double)miss_pjob_number_ / total_pjob_number_;
    double average_response_time =
        (double)total_response_time_ / finished_ajob_number_;

    cout << "Miss rate: " << miss_rate << endl;
    cout << "Average response time: " << average_response_time << endl;
}
