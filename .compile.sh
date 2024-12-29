#!/bin/bash

OUTPUT=".program"
DEPENDENCIES=""

# Parse flags
for flag in "$@"; do
  case $flag in
  -o=* | --output=*)
    OUTPUT="${flag#*=}"
    shift
    ;;
  -d=* | --dependencies=*)
    DEPENDENCIES="${flag#*=}"
    shift
    ;;
  *)
    echo "Error: Unknown flag '$flag'."
    shift
    ;;
  esac
done

gcc -c $(ls *.c | xargs)
gcc *.o -o $OUTPUT $DEPENDENCIES
