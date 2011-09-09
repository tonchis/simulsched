#ifndef __SCHED_LOTTERY__
#define __SCHED_LOTTERY__

#include <vector>
#include <queue>
#include <map>
#include "basesched.h"

struct task {
  int tickets;
  bool   blocked;
};

class SchedLottery : public SchedBase {
  public:
    SchedLottery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(const enum Motivo m);

  private:
    int quantum;
    int current_quantum;
    int total_tickets;
    std::map<int,struct task*> tasks;

    int raffle();
};

#endif

