#include "tasks.h"
#include <cstdlib>
#include <time.h>
#include <cmath>

using namespace std;

void TaskCPU(vector<int> params) { // params: n
	uso_CPU(params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(vector<int> params) { // params: ms_cpu, ms_io,
	uso_CPU(params[0]); // Uso el CPU ms_cpu milisegundos.
	uso_IO(params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(vector<int> params) { // params: ms_cpu, ms_io, ms_cpu, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(params[i]);
		else uso_IO(params[i]);
	}
}

void TaskCon(vector<int> params){
  int n    = (int) params[0];
  int bmin = (int) params[1];
  int bmax = (int) params[2];
  int random;
  srand(time(NULL));

  for(int i = 0; i < n; i++){
    random = rand() % (bmax-bmin) + bmin;
    uso_IO(random);
  }
}

void TaskBatch(vector<int> params){
  int tot = params[0] - 1;
  int blocks = params[1];
  int rest;
  int random;

  srand(time(NULL));

  for(int i = 0; i < tot; i++){
    rest = tot - i;
    if(blocks == 0){
      uso_CPU(rest);
      break;
    }
    random = rand() % 100 + 1;
    if(random <= (int) ceil((double)(100 * blocks / rest))){
      blocks--;
      uso_IO(1);
    }else{
      uso_CPU(1);
    }
  }
}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskCon, 3);
	register_task(TaskBatch, 2);
}
