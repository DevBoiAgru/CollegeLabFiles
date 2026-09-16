#include "helper.hpp"
#include <algorithm>

int main() {
  vector<Process> p = input();

  int currentTime = 0;
  int completed = 0;

  while (completed < p.size()) {
    auto shortest = p.end();

    // Find shortest available process
    for (auto it = p.begin(); it != p.end(); it++) {
      // Skip completed processes, and processes not yet arrived.
      if (it->isCompleted() || (it->getArrivalTime() > currentTime)) {
        continue;
      }

      // Check if process is shorter than currently selected. If current shortest process is null, set it directly
      if (shortest == p.end() || it->getBurstTime() < shortest->getBurstTime()) {
        shortest = it;
      }
    }

    // If no process has arrived, CPU is idle
    if (shortest == p.end()) {
      currentTime++;
      continue;
    }

    // Execute process until it's completed
    while (!shortest->isCompleted()) {
      currentTime++;
      shortest->execute(currentTime);
    }
    completed++;
  }

  output(p);
}
