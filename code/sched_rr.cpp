#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
  quantum         = argn[0];
  current_quantum = 0;
}

void SchedRR::load(int pid) {
  round.push(pid);
}

void SchedRR::unblock(int pid) {
  // te felicito.
}

int SchedRR::tick(const enum Motivo m) {
  int next_pid;
  current_quantum++;

  switch(m){
    case EXIT:
      current_quantum = 0;
      if (round.empty()){
        next_pid = IDLE_TASK;
      }else{
        next_pid = round.front();
        round.pop();
      }
      break;
    default:
      if(current_quantum == quantum - 1){
        next_pid = round.front();
        round.pop();
        round.push(current_pid());
        current_quantum = 0;
      }else{
        next_pid = current_pid();
      }
      return next_pid;
      break;
  }

  return next_pid;
}

