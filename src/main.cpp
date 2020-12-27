#include <iostream>
#include <string>
#include <vector>

#include "AperiodicTask.h"
#include "AperiodicTasks.h"
#include "Job.h"
#include "Task.h"
#include "Utility.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Usage:" << endl;
        cout << argv[0] << " periodic.txt aperiodic.txt" << endl;
        return -1;
    }

    string task_file = argv[1];
    string aperiodic_task_file = argv[2];

    vector<Task> tasks = read_tasks(task_file);
    AperiodicTasks atasks;
    atasks.load_from_file(aperiodic_task_file);

    cout << "periodicTasks:" << endl;
    for (auto& task : tasks) {
        cout << task.to_string() << endl;
    }

    cout << "aperiodicTasks:" << endl;
    for (auto& t : atasks.tasks_) {
        cout << t.second.to_string() << endl;
    }

    return 0;
}
