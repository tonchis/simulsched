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
  round.push(pid);
}

int SchedRR::tick(const enum Motivo m) {
  int next_pid;
  current_quantum++;

  switch(m){
    case EXIT:
    case BLOCK:
      current_quantum = 0;
      round.pop();
      if (round.empty()){
        next_pid = IDLE_TASK;
      }else{
        next_pid = round.front();
      }
      break;
    case TICK:
      if(current_pid() != IDLE_TASK){
        if(current_quantum == quantum){
          next_pid = nextPid();
        }else{
          next_pid = current_pid();
        }
      }else{
        if(round.empty()){
          next_pid = IDLE_TASK;
        }else{
          next_pid = round.front();
          current_quantum = 0;
        }
      }
      break;
    default:
      break;
  }

  return next_pid;
}

int SchedRR::nextPid(){
  int old = round.front();
  round.pop();
  round.push(old);
  current_quantum = 0;
  return round.front();
}

