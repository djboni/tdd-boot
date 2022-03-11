#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

set -e

# Constants
BuildScript="lib/scripts/build.mk"
RunnerCreator="lib/unity/auto/generate_test_runner.rb"

# Command-line options
File="$1"

# Determine file names
Runner="build/${File%.[cC]}_runner.c"
RunnerDir="${Runner%/*}"
Exec="build/${File%.[cC]}.elf"
ExecDir="${Exec%/*}"

set -x

# Create directories
if [ ! -d "$ExecDir" ]; then
    mkdir -p "$ExecDir"
fi
if [ ! -d "$RunnerDir" ]; then
    mkdir -p "$RunnerDir"
fi

# Create test runner
if [ ! -f "$Runner" ] || [ "$File" -nt "$Runner" ]; then
    ruby $RunnerCreator "$File" "$Runner"
fi

# Build test
make -f $BuildScript \
    EXEC="$Exec" \
    INPUTS="$File $Runner lib/unity/src/unity.c" \
    CPPFLAGS="-D UNITTEST -I lib/unity/src" \
    "$Exec"

# Run test
"$Exec"
