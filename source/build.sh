#!/bin/bash

BUILD_DIRECTORY=build/
LOG_FILE=build-log.log

ask() {
    # http://djm.me/ask
    while true; do

        if [ "${2:-}" = "Y" ]; then
            prompt="Y/n"
            default=Y
        elif [ "${2:-}" = "N" ]; then
            prompt="y/N"
            default=N
        else
            prompt="y/n"
            default=
        fi

        # Ask the question - use /dev/tty in case stdin is redirected from somewhere else
        read -p "$1 [$prompt] " REPLY </dev/tty

        # Default?
        if [ -z "$REPLY" ]; then
            REPLY=$default
        fi

        # Check if the reply is valid
        case "$REPLY" in
            Y*|y*) return 0 ;;
            N*|n*) return 1 ;;
        esac

    done
}

# Guarantees an existing empty build directory or exits.
if [ -d "$BUILD_DIRECTORY" ]; then
  if ! ask "Build directory already exists, do you wish to overwrite the current build?"; then
    { echo "Ok then." 1>&2; exit; }
  else
    echo "Removing build directory."
    rm -rf BUILD_DIRECTORY
    mkdir BUILD_DIRECTORY
  fi
else
  echo "Creating build directory"
  mkdir BUILD_DIRECTORY
fi

# Run cmake build and spit into log file
cd $BUILD_DIRECTORY
cmake ..
cmake -- build . 2>&1 | tee $LOG_FILE

# process arguments
if [[ $# == 1 ]]; then
  if [[ $1 == "run" ]]; then
    ./game
  fi
fi
