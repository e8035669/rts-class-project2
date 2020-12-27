#include "Simulator.h"

Simulator::Simulator()
    : clock_(0),
      max_clock_(0),
      periodic_tasks_(),
      aperiodic_tasks_(),
      total_response_time_(0),
      finished_ajob_number_(0),
      miss_pjob_number_(0),
      total_pjob_number_(0) {}

bool Simulator::run_once() {
    if (clock_ < max_clock_) {
        return false;
    } else {
        return false;
    }
}
