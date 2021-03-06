#include "Utility.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Task.h"

using namespace std;

std::vector<Task> read_tasks(const std::string& file_name) {
    std::vector<Task> ret;
    std::ifstream ifs(file_name);

    for (std::string s; std::getline(ifs, s);) {
        vector<int> contexts;
        stringstream ss(s);
        for (string raw_context; getline(ss, raw_context, ',');) {
            contexts.push_back(stoi(raw_context));
        }
        if (contexts.size() == 2) {
            Task tmp_task;
            tmp_task.period = contexts.at(0);
            tmp_task.execution_time = contexts.at(1);
            tmp_task.task_id = (int)ret.size() + 1;
            ret.push_back(tmp_task);
        }
    }
    return ret;
}

std::vector<std::vector<int>> read_int_content(const std::string& filename) {
    std::vector<std::vector<int>> ret;
    std::ifstream ifs(filename);

    for (std::string s; std::getline(ifs, s);) {
        vector<int> contexts;
        stringstream ss(s);
        for (string raw_context; getline(ss, raw_context, ',');) {
            contexts.push_back(stoi(raw_context));
        }
        ret.push_back(contexts);
    }
    return ret;
}


