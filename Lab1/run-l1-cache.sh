#!/bin/bash

command="build/X86/gem5.opt configs/learning_gem5/part1/two_level.py /gem5/tables_UF/tables.exe --l1i_size=8kB --l1d_size="
options=" --l2_size=128kB"
dataFile="m5out/stats.txt"
pattern="system.cpu.numCycles"
outputFile="l1-cache.txt"

caches=(2 4 8 16 32 64)
for cache in ${caches[@]}
do
    full_options="$cache"
    full_options+="kB"
    full_options+="$options"
    full_command="$command$full_options"
    eval $full_command &&
    < "$dataFile" grep --line-buffered "$pattern" >> "$outputFile" 
done