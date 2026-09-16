#pragma once

#include <iostream>
#include <vector>
#include "process.hpp"

using namespace std;

vector<Process> input(bool inputPriority = false) {
  int n;
  cout << "Enter number of processes: ";
  cin >> n;

  vector<Process> p;

  for (int i = 1; i <= n; i++) {
    int at, bt, pr = 0;

    cout << "\nProcess " << i << '\n';
    cout << "Arrival time: ";
    cin >> at;

    cout << "Burst time: ";
    cin >> bt;
    
    if (inputPriority) {
      cout << "Priority: ";
      cin >> pr;
    }

    p.emplace_back(i, at, bt, pr);
  }

  return p;
}

void output(const vector<Process>& p) {
  double avgTAT = 0, avgWT = 0;

  cout << "\nPID\tAT\tBT\tP\tCT\tTAT\tWT\n";

  for (const auto& x : p) {
    cout << x.getPID() << '\t'
       << x.getArrivalTime() << '\t'
       << x.getBurstTime() << '\t'
       << x.getPriority() << '\t'
       << x.getCompletionTime() << '\t'
       << x.getTurnaroundTime() << '\t'
       << x.getWaitingTime() << '\n';

    avgTAT += x.getTurnaroundTime();
    avgWT += x.getWaitingTime();
  }

  cout << "\nAverage TAT: " << avgTAT / p.size();
  cout << "\nAverage WT: " << avgWT / p.size() << '\n';
}
