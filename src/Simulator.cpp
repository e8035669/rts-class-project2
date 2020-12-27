#include "Simulator.h"

#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

void Simulator::assign_tasks(const vector<Task>& tasks) {
    _tasks = tasks;
    calc_max_clock();
}

void Simulator::calc_max_clock() {
    int max_period = 1;
    int max_phase = 0;
    if (_tasks.size() > 0) {
        for (Task& t : _tasks) {
            max_period = lcm(max_period, t.period);
            max_phase = max(max_phase, t.phase);
        }
        _max_clock = max_period + max_phase;
    }
}

int Simulator::get_max_clock() { return _max_clock; }

bool Simulator::run_one_clock() {
    if (_clock < _max_clock) {
        job_miss_scan();    // 判斷每一工作是否能在絕對截限時間內完成
        job_release_scan(); // 判斷任務是否要加入工作

        if (job_queue.size() > 0) {
            cout << _clock << " T" << job_queue.front().parent_task.task_id
                 << endl;
            // 目前工作執行時間減1
            job_queue.front().remain_execution_time--;

            // 刪除完成的工作
            if (job_queue.front().remain_execution_time == 0) {
                job_queue.pop_front();
            }
        } else {
            cout << _clock << endl;
        }

        // cout << "Jobs: ";
        // for (Job& j : job_queue) {
        //     cout << "T" << j.parent_task.task_id << ", ";
        // }
        // cout << endl;

        _clock++;
    }
    if (_clock < _max_clock) {
        return true;
    } else {
        return false;
    }
}

// 檢查每一工作是否在絕對截限時間內完成
void Simulator::job_miss_scan() {
    for (auto it = job_queue.begin(); it != job_queue.end();) {
        Job& j = *it;
        if (j.absolute_deadline - _clock - j.remain_execution_time < 0) {
            cout << "Job miss: T" << j.parent_task.task_id << endl;
            _miss_deadline_job_number++;

            it = job_queue.erase(it);
        } else {
            ++it;
        }
    }
}

// 檢查是否有新工作抵達
void Simulator::job_release_scan() {
    for (Task& t : _tasks) {
        if ((_clock >= t.phase) && ((_clock - t.phase) % t.period) == 0) {
            Job new_job{.parent_task = t};
            new_job.absolute_deadline = _clock + t.relative_deadline;
            new_job.release_time = _clock;
            new_job.remain_execution_time = t.execution_time;

            // 加入新工作並已排序
            schedule_policy->set_comp_job(&new_job);
            auto insert_point = find_if(job_queue.begin(), job_queue.end(),
                                        ref(*schedule_policy));
            job_queue.insert(insert_point, new_job);
            _total_job_number++;
        }
    }
}

bool Simulator::schedulability_test() {
    double utility = schedule_policy->utility(_tasks);
    double schedulable_utility = schedule_policy->schedulable_utility(_tasks);

    if (utility > schedulable_utility) {
        cout << "U = " << utility << " > " << schedulable_utility
             << ", may not schedulable" << endl;
        return false;
    } else {
        cout << "U = " << utility << " < " << schedulable_utility << ", schedulable"
             << endl;
        return true;
    }
}
int Simulator::get_miss_deadline_job_number() {
    return _miss_deadline_job_number;
}

int Simulator::total_job_number() { return _total_job_number; }
