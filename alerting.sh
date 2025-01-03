#!/bin/bash

COMPILE=0
PRECOMPILE=0
RUN=-1

# Parse flags
for flag in "$@"; do
  case $flag in
  -c | --compile)
    COMPILE=1
    shift
    ;;
  -p | --precompile)
    PRECOMPILE=1
    shift
    ;;
  -R=* | --run=*)
    RUN="${flag#*=}"
    shift
    ;;
  -cp)
    COMPILE=1
    PRECOMPILE=1
    shift
    ;;
  -cR=*)
    COMPILE=1
    RUN="${flag#*=}"
    shift
    ;;
  -pR=*)
    PRECOMPILE=1
    RUN="${flag#*=}"
    shift
    ;;
  -cpR=*)
    COMPILE=1
    PRECOMPILE=1
    RUN="${flag#*=}"
    shift
    ;;
  -h | --help)
    echo -e "\n  Help Panel for 'alerting.sh' Script"
    echo -e "This script should be used to test your settings using --run, to precompile values to be used using --precompile, or to compile the precompiler using --compile, although the last one should only be done once.\n"
    echo -e "Flags:"
    echo -e " -c   | --compile    --> Compiles the precompile program."
    echo -e "                       > Since the binary program is .gitignore-ed, this must be called at least once."
    echo -e " -p   | --precompile --> Runs the precompile script."
    echo -e " -R=* | --run=*      --> Runs the program itself."
    echo -e "                       > The value provided is the battery percentage to test."
    echo -e "                       > If the value provided is 0, it will use the current battery percentage."
    echo -e "Flags can be combined as long as they are in alphabetical order where the --run flag is always last."
    echo -e "The --help flag cannot be combined with any flag.\n"
    exit
    ;;
  *)
    echo "Error: Unknown flag '$flag'."
    exit
    ;;
  esac
done

# Compile program
if [[ $COMPILE -eq 1 ]]; then
  ./precompiler/.compile.sh -i=precompiler/ -o=precompiler/.program
fi

# Precompile values
if [[ $PRECOMPILE -eq 1 ]]; then
  if [[ -f ./precompiler/.program ]]; then
    echo "Error: Precompiler program is not compile, run this script using -c flag to compile the program."
    exit
  else
    ./precompiler/.program
    chmod +x ./precompiled_values.sh
  fi
fi

# Run values using either battery of argument
if [[ $RUN -ne -1 ]]; then
  if [[ $RUN -eq 0 ]]; then
    ./reference.sh
  else
    ./script.sh "$RUN"
  fi
fi
