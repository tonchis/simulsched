#include "sched_lottery.h"
#include "basesched.h"

using namespace std;

SchedLottery::SchedLottery(vector<int> argn) {
  seed            = argn[0];
  quantum         = argn[1];
  current_quantum = 0;
}

void SchedLottery::load(int pid) {
  tasks.insert(pair<int, double>(pid, (double) 10));
}

void SchedLottery::unblock(int pid) {
}

int SchedLottery::tick(const enum Motivo m) {
  int next_pid;
  current_quantum++;

  switch(m){
    case EXIT:
      current_quantum = 0;
      // remove current from tasks

      if (tasks.empty()){
        next_pid = IDLE_TASK;
      }else{
        // hold a lottery and chose the winner!
        // next_pid = winner.pid;
      }
      break;
    case BLOCK:
      // remove from tasks??
      tasks[current_pid()] += (double) quantum/current_quantum;
      // hold a lottery and chose the winner!
      // next_pid = winner.pid;
      break;
    case TICK:
      if(current_pid() != IDLE_TASK){
        if(current_quantum == quantum){
          // hold a lottery and chose the winner!
          // next_pid = winner.pid;
        }else{
          next_pid = current_pid();
        }
      }else{
        if(tasks.empty()){
          next_pid = IDLE_TASK;
        }else{
          // hold a lottery and chose the winner!
          // next_pid = winner.pid;
        }
      }
      break;
    default:
      break;
  }

  return next_pid;
}

