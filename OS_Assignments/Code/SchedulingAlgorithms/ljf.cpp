#include "helper.hpp"
#include <algorithm>

int main() {
  vector<Process> p = input();

  int currentTime = 0;
  int completed = 0;

  while (completed < p.size()) {
    auto longest = p.end();

    // Find longest available process
    for (auto it = p.begin(); it != p.end(); it++) {
      // Skip completed processes, and processes not yet arrived.
      if (it->isCompleted() || (it->getArrivalTime() > currentTime)) {
        continue;
      }

      // Check if process is longer than currently selected. If current longestprocess is null, set it directly
      if (longest == p.end() || it->getBurstTime() > longest->getBurstTime()) {
        longest = it;
      }
    }

    // If no process has arrived, CPU is idle
    if (longest == p.end()) {
      currentTime++;
      continue;
    }

    // Execute process until it's completed
    while (!longest->isCompleted()) {
      currentTime++;
      longest->execute(currentTime);
    }
    completed++;
  }

  output(p);
}
