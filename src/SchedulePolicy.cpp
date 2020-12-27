#include "SchedulePolicy.h"

#include <vector>

#include "Job.h"
#include "Task.h"

bool SchedulePolicy::operator()(const Job& j) const { return compare(j); }

double SchedulePolicy::utility(const std::vector<Task>& tasks) {
    double ret = 0;
    for (const Task& t : tasks) {
        ret += t.utilization();
    }
    return ret;
}

// EDF排程 根據絕對截限時間排序
bool EDF::compare(const Job& j) const {
    assert(comp_job != nullptr);
    return comp_job->absolute_deadline < j.absolute_deadline;
}

double EDF::schedulable_utility(const std::vector<Task>& tasks) { return 1; }

// RM排程 根據週期排序
bool RM::compare(const Job& j) const {
    assert(comp_job != nullptr);
    return comp_job->parent_task.period < j.parent_task.period;
}

double RM::schedulable_utility(const std::vector<Task>& tasks) {
    if (tasks.size() > 0) {
        double n = tasks.size();
        return n * (pow(2, 1 / n) - 1);
    }
    return 0;
}
