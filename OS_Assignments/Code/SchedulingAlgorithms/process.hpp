#pragma once

class Process {
  unsigned int m_id;
  int m_arrivalTime;
  int m_burstTime;
  int m_priority;
  int m_remainingTime;
  int m_completionTime = -1;

public:
  Process(unsigned int id, int arrivalTime,
      int burstTime, int priority = 0)
    : m_id(id), m_arrivalTime(arrivalTime),
      m_burstTime(burstTime), m_priority(priority),
      m_remainingTime(burstTime) {}

  unsigned int getPID() const { return m_id; }
  int getArrivalTime() const { return m_arrivalTime; }
  int getBurstTime() const { return m_burstTime; }
  int getPriority() const { return m_priority; }
  int getRemCPUTime() const { return m_remainingTime; }
  int getCompletionTime() const { return m_completionTime; }

  int getTurnaroundTime() const {
    return m_completionTime - m_arrivalTime;
  }

  int getWaitingTime() const {
    return getTurnaroundTime() - m_burstTime;
  }

  bool isCompleted() const {
    return m_remainingTime == 0;
  }

  void execute(int currentTime) {
    m_remainingTime--;

    if (isCompleted())
      m_completionTime = currentTime;
  }
};
