#!/bin/bash

# this is the first part of the command that must be executed
command="build/X86/gem5.opt configs/learning_gem5/part1/two_level.py /gem5/tables_UF/"
# this is the file where the output of the command will be stored by gem5
dataFile="m5out/stats.txt"
# this is the pattern that we are looking for in the output file
pattern="system.cpu.numCycles"
# this is the file where our data will be stored
outputFile="combinations.csv"

echo "cycles,l1i,l1d,l2,uf" > "$outputFile"

l1i_cache=(2 4 8 16 32 64)
l1d_cache=(2 4 8 16 32 64)
l2_cache=(128 256 512 1024)
unrolling_factors=(2 4 8 16 32)
for l1i in ${l1i_cache[@]}
do
    # we construct the options to be passed to the command
    l1i_opt="--l1i_size="
    l1i_opt+="$l1i"
    l1i_opt+="kB"
    for l1d in ${l1d_cache[@]}
    do
        l1d_opt="--l1d_size="
        l1d_opt+="$l1d"
        l1d_opt+="kB"
        for l2 in ${l2_cache[@]}
        do
            l2_opt="--l2_size="
            l2_opt+="$l2"
            l2_opt+="kB"
            for uf in ${unrolling_factors[@]}
            do
                uf_opt="tables_uf"
                uf_opt+="$uf"
                uf_opt+=".exe"

                # we construct the full command to be executed
                full_command="$command$uf_opt $l1i_opt $l1d_opt $l2_opt"
                # we execute the command
                eval $full_command && # if it is successful
                # we extract the data we are interested in
                cycles="$(< "$dataFile" grep --line-buffered "$pattern")" &&
                # and we write it to the output file in csv format
                echo "$cycles,$l1i,$l1d,$l2,$uf" >> "$outputFile"
            done
        done
    done
done
# the csv is not in the correct format yet
# because cycles did not contain only the number of cycles
# but also two strings and whitespaces that we do not need

# to remove the system.cpu.numCycles from every line
sedPattern1="s/system.cpu.numCycles//g"
# to remove the "# Number of cpu cycles simulated (Cycle)" from every line
sedPattern2="s/# Number of cpu cycles simulated (Cycle)//g"
# to remove the spaces from every line
sedPattern3="s/\s//g"
# give the patterns to sed
sed -i "$sedPattern1; $sedPattern2; $sedPattern3" "$outputFile"