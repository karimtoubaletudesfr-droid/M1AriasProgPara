#!/bin/bash

SIZES=(6000000 60000000 120000000 300000000 600000000)
PROCS=(1 2 4 6)

echo "np,size,time"

for np in "${PROCS[@]}"; do
    for size in "${SIZES[@]}"; do

        echo "Test np=$np size=$size"

        output=$(mpirun -np "$np" ./maxtab "$size")

        time=$(echo "$output" | grep "Temps d'execution" | awk '{print $(NF-1)}')

        echo "$np,$size,$time"
    done
done