#!/bin/bash

INPUT=""
FILES="*.c"
OUTPUT=".program"
DEPENDENCIES=""
FORCE=0
DELETE_OBJECTS=0

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
  -i=* | --path=*)
    INPUT="${flag#*=}"
    shift
    ;;
  -f=* | --file=*)
    FILES="${flag#*=}"
    shift
    ;;
  -F | --force)
    FORCE=1
    shift
    ;;
  -D | --delete-objects)
    DELETE_OBJECTS=1
    shift
    ;;
  *)
    echo "Error: Unknown flag '$flag'."
    exit
    ;;
  esac
done

# Delete object files if -F flag is present
if [[ DELETE_OBJECTS -eq 1 ]]; then
  if [[ FORCE -eq 1 ]]; then
    rm *.o
  else
    echo "Warning: Cannot delete objects since it is not forced. Use flag -F to force."
  fi
fi

# Check for object files in the same directory if not forced
if [[ FORCE -eq 0 ]]; then
  if [[ -f *.o ]]; then
    echo "Warning: There are already .o files in this directory, they might be moved to a different directory."
  fi
  if ! ls $INPUT*.c &>/dev/null; then
    echo "Error: There are no files to compile at '$INPUT'."
    exit
  fi
fi

gcc -c $(ls $INPUT$FILES | xargs)
if [[ $INPUT != "" ]]; then
  mv *.o $INPUT
fi
gcc $INPUT*.o -o $OUTPUT $DEPENDENCIES
