#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "AperiodicTask.h"

struct AperiodicTasks {
    AperiodicTasks();

    void load_from_file(const std::string& filename);

    std::vector<AperiodicTask> getAperiodicTask(int phase);

    std::unordered_multimap<int, AperiodicTask> tasks_;
};
