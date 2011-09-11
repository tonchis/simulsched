#include "sched_lottery.h"
#include "basesched.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

SchedLottery::SchedLottery(vector<int> argn) {
  srand((unsigned int) argn[0]);
  quantum         = argn[1];
  total_tickets   = 0;
  current_quantum = 0;
}

void SchedLottery::load(int pid) {
  struct task* new_task = new struct task;
  new_task->tickets = 1;
  new_task->blocked = false;
  tasks[pid] = new_task;
  total_tickets += new_task->tickets;
}

void SchedLottery::unblock(int pid) {
  tasks[pid]->blocked = false;
  total_tickets += tasks[pid]->tickets;
}

int SchedLottery::tick(const enum Motivo m) {
  int next_pid;
  int compensation_tickets;
  double compensation_fraction;
  int remaining_quantum;
  struct task* current_task;
  current_quantum++;

  switch(m){
    case EXIT:
      current_quantum = 0;
      current_task = tasks[current_pid()];
      tasks.erase(current_pid());
      total_tickets -= current_task->tickets;
      delete current_task;

      if (total_tickets <= 0){
        next_pid = IDLE_TASK;
      }else{
        next_pid = raffle();
      }
      break;
    case BLOCK:
      remaining_quantum = quantum - current_quantum;
      if(remaining_quantum > 0){
        compensation_fraction = (double) (quantum/remaining_quantum);
        compensation_tickets = (int) ceil(compensation_fraction);
      }else{
        compensation_tickets = 0;
      }

      tasks[current_pid()]->blocked = true;
      total_tickets -= tasks[current_pid()]->tickets;
      tasks[current_pid()]->tickets += compensation_tickets;

      if(total_tickets <= 0){
        next_pid = IDLE_TASK;
      }else{
        next_pid = raffle();
      }
      break;
    case TICK:
      if(current_pid() != IDLE_TASK){
        if(current_quantum == quantum){
          current_quantum = 0;
          next_pid = raffle();
        }else{
          next_pid = current_pid();
        }
      }else{
        if(total_tickets <= 0){
          next_pid = IDLE_TASK;
        }else{
          current_quantum = 0;
          next_pid = raffle();
        }
      }
      break;
    default:
      break;
  }

  return next_pid;
}

// http://www.wordreference.com/es/translation.asp?tranword=raffle
int SchedLottery::raffle(){
  int random  = rand() % total_tickets + 1;
  int acum = 0;

  std::map<int,struct task*>::iterator it;
  for(it = tasks.begin(); it != tasks.end(); it++){
    if(!it->second->blocked){
      acum += it->second->tickets;
      if(acum >= random)
        return it->first;
    }
  }

  perror("No hubo ganador");
  exit(1);
  return -1;
}
