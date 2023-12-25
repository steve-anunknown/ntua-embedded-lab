#!/bin/bash

link_dir="../synch_implementations"
include_dir="../synch_implementations"
gcc_options="-pthread -lcdsl -no-pie -L$link_dir -I$include_dir"

source="dijkstra.c"
input="input.dat"
defs=("SLL" "DLL" "DYN_ARR")

footprints="mem_footprints.out"
accesses="mem_accesses.out"

correct_output="paths.out"

./dijkstra "${input}" > "${correct_output}"

for def in "${defs[@]}"; do
    target="dijkstra_${def}"
    current_output="paths_${def}.out"

    # compile with the current configuration
    gcc -D"${def}" -o "${target}" "${source}" ${gcc_options} &&

    # run the program
    ./"${target}" "${input}" > "${current_output}"

    # compare the output with the correct one
    if diff -q "${correct_output}" "${current_output}" >/dev/null; then
        echo "The outputs are identical"
    else
        echo "The outputs are different"
    fi

    # get memory accesses
    temp_file=$(mktemp)
    valgrind --log-file="$temp_file" --tool=lackey --trace-mem=yes ./"${target}" "${input}"
    grep -c 'I\| L' "$temp_file" >> "${accesses}"

    # get memory footprint
    valgrind --tool=massif --massif-out-file="${temp_file}" ./"${target}" "${input}"
    temp_file2=$(mktemp)
    ms_print "${temp_file}" > "${temp_file2}"
    grep '\^' "${temp_file2}" | cut -d'^' -f1 >> "${footprints}"
    rm "${temp_file}" "${temp_file2}"
done
