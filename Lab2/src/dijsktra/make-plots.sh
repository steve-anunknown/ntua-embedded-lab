#!/bin/bash

gnuplot << EOF
set terminal png
set output "mem_access.png"
set title "Memory accesses"
set xlabel "Data structure"
set ylabel "Number of memory accesses"
set xtics rotate by -30
set xtics ("SLL" 0, "DLL" 1, "DYN ARR" 2)
set boxwidth 0.5
set style fill solid
unset key
plot "mem_accesses.out" using 1:xtic(2) with boxes

set terminal png
set output "mem_footprint.png"
set title "Memory footprint"
set xlabel "Data structure"
set ylabel "Memory footprint (kB)"
set xtics rotate by -30
set xtics ("SLL" 0, "DLL" 1, "DYN ARR" 2)
set boxwidth 0.5
set style fill solid
unset key
plot "mem_footprints.out" using 1:xtic(2) with boxes
EOF