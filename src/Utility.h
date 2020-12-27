#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Task.h"

std::vector<Task> read_tasks(const std::string& file_name);
std::vector<std::vector<int>> read_int_content(
    const std::string& filename);
