#ifndef __SCHED_LOTTERY__
#define __SCHED_LOTTERY__

#include <vector>
#include <queue>
#include "basesched.h"

struct task {
  int pid;
  double tickets;
};

class SchedLottery : public SchedBase {
  public:
    SchedLottery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(const enum Motivo m);

  private:
    int seed;
    int quantum;
    std::vector<task> tasks;
};

#endif
