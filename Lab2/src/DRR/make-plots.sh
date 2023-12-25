#!/bin/bash

# use gnuplot to plot memory accesses
# for all configurations

gnuplot << EOF
set terminal png
set output "mem_accesses.png"
set title "Memory accesses"
set xlabel "Configuration (CL, PK)"
set ylabel "Memory accesses"
set xtics rotate by -30
set xtics ("(sll, sll)" 0, "(sll, dll)" 1, "(sll, dyn arr)" 2, "(dll, sll)" 3, "(dll, dll)" 4, "(dll, dyn arr)" 5, "(dyn arr, sll)" 6, "(dyn arr, dll)" 7, "(dyn arr, dyn arr)" 8)
set boxwidth 0.5
set style fill solid
unset key
plot "mem_accesses.txt" using 1:xtic(2) with boxes

set terminal png
set output "mem_footprint.png"
set title "Memory footprint"
set xlabel "Configuration (CL, PK)"
set ylabel "Memory footprint (kB)"
set xtics rotate by -30
set xtics ("(sll, sll)" 0, "(sll, dll)" 1, "(sll, dyn arr)" 2, "(dll, sll)" 3, "(dll, dll)" 4, "(dll, dyn arr)" 5, "(dyn arr, sll)" 6, "(dyn arr, dll)" 7, "(dyn arr, dyn arr)" 8)
set boxwidth 0.5
set style fill solid
unset key
plot "mem_footprints.out" using 1:xtic(2) with boxes
EOF