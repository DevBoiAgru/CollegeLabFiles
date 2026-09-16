#include "helper.hpp"
#include <algorithm>

int main() {
  vector<Process> p = input(true);

  int currentTime = 0;
  int completed = 0;

  while (completed < p.size()) {
    auto highest = p.end();

    // Find highest priority available process
    for (auto it = p.begin(); it != p.end(); it++) {
      // Skip completed processes and processes not yet arrived.
      if (it->isCompleted() || it->getArrivalTime() > currentTime) {
        continue;
      }

      // Lower number = Lower priority
      if (highest == p.end() || it->getPriority() > highest->getPriority()) {
        highest = it;
      }
    }

    // If no process has arrived, CPU is idle
    if (highest == p.end()) {
      currentTime++;
      continue;
    }

    // Execute process until it's completed
    while (!highest->isCompleted()) {
      currentTime++;
      cout << "Executing P" << highest->getPID() << endl;
      highest->execute(currentTime);
    }

    completed++;
  }

  output(p);
}
