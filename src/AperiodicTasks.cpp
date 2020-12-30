#include "AperiodicTasks.h"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "AperiodicTask.h"
#include "Utility.h"

using namespace std;

AperiodicTasks::AperiodicTasks() {}

void AperiodicTasks::load_from_file(const std::string& filename) {
    tasks_.clear();

    vector<vector<int>> contents = read_int_content(filename);
    for (size_t i = 0; i < contents.size(); ++i) {
        auto& content = contents[i];
        if (content.size() == 2) {
            tasks_.insert(
                {content[0], AperiodicTask(i + 1, content[0], content[1])});
        } else {
            cout << "Ignore line " << i << endl;
        }
    }
}

std::vector<AperiodicTask*> AperiodicTasks::getAperiodicTask(int phase) {
    std::vector<AperiodicTask*> ret;
    auto range = tasks_.equal_range(phase);
    for (auto it = range.first; it != range.second; ++it) {
        ret.push_back(&it->second);
    }
    return ret;
}
