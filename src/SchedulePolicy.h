#pragma once

#include <cassert>
#include <cmath>
#include <vector>

#include "Job.h"

struct SchedulePolicy {
    Job* comp_job = nullptr;

    void set_comp_job(Job* j) { comp_job = j; }
    virtual bool compare(const Job& j) const = 0;
    bool operator()(const Job& j) const;

    static double utility(const std::vector<Task>& tasks);
    virtual double schedulable_utility(const std::vector<Task>& tasks) = 0;
};

struct EDF : SchedulePolicy {
    bool compare(const Job& j) const override;
    double schedulable_utility(const std::vector<Task>& tasks) override;
};

struct RM : SchedulePolicy {
    bool compare(const Job& j) const override;
    double schedulable_utility(const std::vector<Task>& tasks) override;
};
