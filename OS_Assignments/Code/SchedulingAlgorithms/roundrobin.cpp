#include "helper.hpp"
#include <deque>
#include <algorithm>

int main() {
  vector<Process> p = input();

  int quantum;
  cout << "Enter time quantum: ";
  cin >> quantum;

  deque<Process*> readyQueue;

  int currentTime = 0;
  int completed = 0;

  while (completed < p.size()) {

    // Add arrived processes to ready queue
    for (auto& process : p) {
      bool completed = process.isCompleted();

      if (process.isCompleted() || process.getArrivalTime() > currentTime) {
        continue;
      }

      bool alreadyInQueue =
        find(readyQueue.begin(), readyQueue.end(), &process)
        != readyQueue.end();

      if (alreadyInQueue)
        continue;

      readyQueue.push_back(&process);
    }


    // CPU idle
    if (readyQueue.empty()) {
      currentTime++;
      continue;
    }

    Process* process = readyQueue.front();
    readyQueue.pop_front();

    // Execute for one quantum
    for (int t = 0; t < quantum && !process->isCompleted(); t++) {

      currentTime++;
      process->execute(currentTime);

      // Add processes arriving during in between the quantum
      for (auto& process : p) {
        if (!process.isCompleted() && process.getArrivalTime() == currentTime) {
          readyQueue.push_back(&process);
        }
      }
    }

    if (process->isCompleted())
      completed++;
    else
      readyQueue.push_back(process);
  }

  output(p);
}
