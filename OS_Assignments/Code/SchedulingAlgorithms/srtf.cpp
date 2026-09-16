#include "helper.hpp"
#include <algorithm>

int main() {
  vector<Process> p = input();

  int currentTime = 0;
  int completed = 0;

  while (completed < p.size()) {
    auto shortest = p.end();

    // Find shortest available remaining time
    for (auto it = p.begin(); it != p.end(); it++) {

      // Skip completed processes and processes not yet arrived.
      if (it->isCompleted() || it->getArrivalTime() > currentTime) {
        continue;
      }

      if (shortest == p.end() || (it->getRemCPUTime() < shortest->getRemCPUTime())) {
        shortest = it;
      }
    }

    // If no process has arrived, CPU is idle
    if (shortest == p.end()) {
      currentTime++;
      continue;
    }

    // Execute for one time unit
    currentTime++;
    shortest->execute(currentTime);

    if (shortest->isCompleted())
      completed++;
  }

  output(p);
}
