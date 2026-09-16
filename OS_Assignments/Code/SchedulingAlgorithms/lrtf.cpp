#include "helper.hpp"
#include <algorithm>

int main() {
  vector<Process> p = input();

  int currentTime = 0;
  int completed = 0;

  while (completed < p.size()) {
    auto longest = p.end();

    // Find longest available remaining time
    for (auto it = p.begin(); it != p.end(); it++) {

      // Skip completed processes and processes not yet arrived.
      if (it->isCompleted() || it->getArrivalTime() > currentTime) {
        continue;
      }

      if (longest == p.end() || (it->getRemCPUTime() > longest->getRemCPUTime())) {
        longest = it;
      }
    }

    // If no process has arrived, CPU is idle
    if (longest == p.end()) {
      currentTime++;
      continue;
    }

    // Execute for one time unit
    currentTime++;
    longest->execute(currentTime);

    if (longest->isCompleted())
      completed++;
  }

  output(p);
}
