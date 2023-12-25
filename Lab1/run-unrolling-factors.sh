#!/bin/bash

command="build/X86/gem5.opt configs/learning_gem5/part1/two_level.py /gem5/tables_UF/"
options="--l1i_size=8kB --l1d_size=8kB --l2_size=128kB"
dataFile="m5out/stats.txt"
pattern="system.cpu.numCycles"
outputFile="unrolling-factors.txt"

factors=(2 4 8 16 32)
for factor in ${factors[@]}
do
    executable="tables_uf"
    executable+="$factor"
    executable+=".exe"
    full_command="$command$executable $options"
    eval $full_command &&
    < "$dataFile" grep --line-buffered "$pattern" >> "$outputFile"
done