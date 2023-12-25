#!/bin/bash

link_dir="../synch_implementations"
include_dir="../synch_implementations"
gcc_options="-pthread -lcdsl -no-pie -L$link_dir -I$include_dir"

target="drr"
source="drr.c"
defs_cl=("SLL_CL" "DLL_CL" "DYN_ARR_CL")
defs_pk=("SLL_PK" "DLL_PK" "DYN_ARR_PK")

mem_log="mem_accesses_log.txt" # this gets overwritten in each iteration
accesses_out="mem_accesses.txt" # this stores the mem accesses of each config
mem_footprint="mem_footprint_log.txt" # this accumulates the mem logs
mem_footprints_out="mem_footprints.out" # this keeps the footprints from the logs


for def_cl in "${defs_cl[@]}"; do
    for def_pk in "${defs_pk[@]}"; do
        massif_out="massif_""$def_cl""_""$def_pk"".out"
        # compile with the current configuration
        gcc -D"$def_cl" -D"$def_pk" -o $target $source "$gcc_options" &&
        # get memory accesses
        valgrind --log-file="$mem_log" --tool=lackey --trace-mem=yes "./$target" &&
        grep -c 'I\| L' "$mem_log" >> "$accesses_out"
        # get memory footprint
        valgrind --tool=massif --massif-out-file="$massif_out" "./$target" &&
        ms_print "$massif_out" >> $mem_footprint
    done
done

grep '\^' $mem_footprint | cut -d'^' -f1 > $mem_footprints_out
