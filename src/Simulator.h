#pragma once

#include <list>
#include <memory>

#include "Job.h"
#include "SchedulePolicy.h"
#include "Task.h"

class Simulator {
    std::vector<Task> _tasks;
    int _total_job_number;
    int _miss_deadline_job_number;
    int _clock;
    int _max_clock;
    std::list<Job> job_queue;
    std::unique_ptr<SchedulePolicy> schedule_policy;

   public:
    Simulator()
        : _tasks(),
          _total_job_number(0),
          _miss_deadline_job_number(0),
          _clock(0),
          _max_clock(0),
          job_queue(),
          schedule_policy(){};

    void assign_tasks(const std::vector<Task>& tasks);

    void calc_max_clock();

    int get_max_clock();

    bool run_one_clock();

    void job_miss_scan();

    void job_release_scan();

    template <class Policy>
    void set_schedule_policy() {
        schedule_policy.reset(new Policy);
    }

    bool schedulability_test();

    int get_miss_deadline_job_number();

    int total_job_number();
};
