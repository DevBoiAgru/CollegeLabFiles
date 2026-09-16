#include "helper.hpp"
#include <algorithm>

int main() {
  vector<Process> p = input();

  // Sort on basis of arrival time
  sort(p.begin(), p.end(), [](auto& a, auto& b) {
    return a.getArrivalTime() < b.getArrivalTime();
  });

  int currentTime = 0;
  for (auto& process : p) {
    // If arrival time of process is greater than current time, CPU is idle so jump to it's arrival time
    currentTime = max(currentTime, process.getArrivalTime());

    // Execute process until it's completed
    while (!process.isCompleted()) {
      currentTime++;
      process.execute(currentTime);
    }
  }

  output(p);
}
