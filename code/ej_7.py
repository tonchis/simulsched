import os

for i in range(0, 10):
  quantum = (i + 1)
  os.system("./simusched lote_batch.tsk 1 SchedRR %i | ./graphsched.py > out_batch%i.png" %(quantum, quantum))

