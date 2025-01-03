#!/bin/bash
# (T^N)((B-A)/(100^N))+A
A=$1 # Starting color   --- A is an integer in [1,255]
B=$2 # Final color      --- B is an integer in [1,255]
N=$3 # Interpolation d. --- N is an integer
T=$4 # Parametric T     --- T is an integer in [0,100]

O=$(bc -l <<<"($T^$N)*(($B-$A)/(100^$N))+$A")

echo $O | cut -d '.' -f 1
