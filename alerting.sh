#!/bin/bash

PRECOMPILE=0
COMPILE=0
RUN=0

# Parse flags
for flag in "$@"; do
  case $flag in
  -p | --precompile)
    PRECOMPILE=1
    shift
    ;;
  -c | --recompile)
    COMPILE=1
    shift
    ;;
  -rc | --re-precompile)
    PRECOMPILE=1
    COMPILE=1
    shift
    ;;
  -R | --run)
    RUN=1
    shift
    ;;
  -Rc | --run-compile)
    RUN=1
    COMPILE=1
    shift
    ;;
  -Rrc | --run-re-precompile)
    RUN=1
    PRECOMPILE=1
    COMPILE=1
    shift
    ;;
  -pr | --run-precompile)
    RUN=1
    PRECOMPILE=1
    shift
    ;;
  *)
    echo "Error: Unknown flag '$flag'."
    exit
    shift
    ;;
  esac
done

if [[ $COMPILE -eq 1 ]]; then
  ./precompiler/.compile.sh -i=precompiler/ -o=precompiler/.program
fi

if [[ $PRECOMPILE -eq 1 ]]; then
  ./precompiler/.program
  chmod +x ./precompiled_values.sh
fi

if [[ $RUN -eq 1 ]]; then
  ./script.sh
fi
