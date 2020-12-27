#include <iostream>
#include <string>
#include <vector>

#include "Job.h"
#include "SchedulePolicy.h"
#include "Simulator.h"
#include "Task.h"
#include "Utility.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc < 2) {
        cout << "Usage:" << endl;
        cout << argv[0] << " task_data.txt [RM|EDF]" << endl;
        return -1;
    }

    string task_file = argv[1];
    string method = "RM";
    if (argc > 2) {
        method = argv[2];
    }

    // 將任務資料讀入
    vector<Task> tasks = read_tasks(task_file);

    cout << "Tasks: " << endl;
    for (const Task& t : tasks) {
        cout << t.ToString() << endl;
    }

    Simulator simulator;

    // 加入任務
    simulator.assign_tasks(tasks);
    // 設定排程方法
    if (method == "RM") {
        simulator.set_schedule_policy<RM>();
    } else {
        simulator.set_schedule_policy<EDF>();
    }
    // 顯示是否可排
    simulator.schedulability_test();

    cout << "Max clock: " << simulator.get_max_clock() << endl;

    bool run = true;
    while (run) {
        run = simulator.run_one_clock();
    }

    // 顯示工作數量
    cout << "total_job_number: " << simulator.total_job_number() << endl;
    cout << "miss_deadline_job_number: "
         << simulator.get_miss_deadline_job_number() << endl;

    return 0;
}
