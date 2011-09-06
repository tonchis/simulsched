#include <vector>
#include <queue>
#include "sched_lottery.h"
#include "basesched.h"

using namespace std;

SchedLottery::SchedLottery(vector<int> argn) {
  seed    = argn[0];
  quantum = argn[1];
}

void SchedLottery::load(int pid) {
}

void SchedLottery::unblock(int pid) {
}

int SchedLottery::tick(const enum Motivo m) {
}
