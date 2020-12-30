#include <iostream>
#include <string>
#include <vector>

#include "AperiodicJob.h"
#include "AperiodicTask.h"
#include "AperiodicTasks.h"
#include "Job.h"
#include "Simulator.h"
#include "Task.h"
#include "Utility.h"
#include "clipp.h"

using namespace std;

struct Parameter {
    string task_file;
    string aperiodic_task_file;
    int max_clock = 1000;
    double server_size = 0.2;
    Simulator::Mode mode = Simulator::Mode::CUS;
};

bool parse_args(Parameter& param, int argc, char** argv) {
    using namespace clipp;
    auto cli =
        (value("periodic task", param.task_file).doc("periodic task file."),
         value("aperiodic task", param.aperiodic_task_file)
             .doc("aperiodic task file"),
         (option("-c", "--max_clock") & value("max_clock", param.max_clock))
             .doc("specify max clock (default: 1000)"),
         (option("-s", "--server_size") &
          value("server_size", param.server_size))
             .doc("set server size (default: 0.2)"),
         (option("-m", "--mode") &
          (command("CUS").set(param.mode, Simulator::Mode::CUS) |
           command("TBS").set(param.mode, Simulator::Mode::TBS)))
             .doc("set mode (default: CUS)"));

    if (!parse(argc, argv, cli)) {
        cout << make_man_page(cli, argv[0]) << endl;
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    Parameter param;
    if (!parse_args(param, argc, argv)) {
        return -1;
    }

    string task_file = param.task_file;
    string aperiodic_task_file = param.aperiodic_task_file;

    vector<Task> tasks = read_tasks(task_file);
    AperiodicTasks atasks;
    atasks.load_from_file(aperiodic_task_file);

    /*
    cout << "periodicTasks:" << endl;
    for (auto& task : tasks) {
        cout << task.to_string() << endl;
    }

    cout << "aperiodicTasks:" << endl;
    for (auto& t : atasks.tasks_) {
        cout << t.second.to_string() << endl;
    }
    */

    Simulator simulator;
    simulator.set_max_clock(param.max_clock);
    simulator.set_server_size(param.server_size);
    simulator.set_aperiodic_server_mode(param.mode);

    simulator.assign_ptasks(tasks);
    simulator.assign_atasks(atasks);

    while (simulator.run_once())
        ;

    simulator.print_statistics();

    return 0;
}
