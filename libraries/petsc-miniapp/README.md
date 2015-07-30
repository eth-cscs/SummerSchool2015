For more information, see the notes in the .c files here

Quick start on daint:

1. Log in, with X tunneling, to daint
    ssh -X user1234@ela.cscs.ch
    ssh -X user1234@daint

2. load modules
    module load PrgEnv-cray [if needbe - unload any other active PrgEnv module first]
    module load cray-petsc

3. Build the executable
    make

4. Test in an interactive session 
    salloc
    cd /path/to/this/directory
    make test

    [Note: you can also modify the included job.daint and submit with sbatch]
    [Note: you will see a difference due the job number. This could be fix with more bash scripting]

5. Run your own experiments
    aprun -n 4 ./main -nx 99 -ny 88 -ts_monitor -snes_monitor -ksp_monitor -dump 1
    aprun -n 1 ./main -nx 16 -ny 16 -ts_monitor -snes_monitor -ksp_monitor -assemble 1 -pc_type gamg

To view the .bov file that is generated (only for single-processor runs with the -dump option), we borrow the procedure from the miniapp
    module load python/2.7.6
    python plotting.py
    display output.png [make sure that you used ssh -X to log in]
