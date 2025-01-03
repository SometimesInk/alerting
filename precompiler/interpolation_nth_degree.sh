#!/bin/bash
# (T^N)((B-A)/(100^N))+A
A=$1 # Starting color   --- A is an integer in [1,255]
B=$2 # Final color      --- B is an integer in [1,255]
N=$3 # Extra arg.       --- N is an integer, which in this case is used as the degree of the monomial equation
T=$4 # Parametric T     --- T is an integer in [0,100]
C=$5 # Color component  --- C is an integer in [0,2] where C=0 means that the color sent is red, C=1 means that the color send is green, C=2 means that the color send is blue

OUT=$(bc -l <<<"($T^$N)*(($B-$A)/(100^$N))+$A")

echo "$OUT" | cut -d '.' -f 1
