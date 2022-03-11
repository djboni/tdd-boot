#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

# Constants
BuildScript="lib/scripts/build.mk"
RunnerCreator="lib/unity/auto/generate_test_runner.rb"

DoRunTest() {

    # Arguments
    File="$1"

    # Determine file names and directories
    Runner="build/${File%.[cC]}_runner.c"
    RunnerDir="${Runner%/*}"
    Exec="build/${File%.[cC]}.elf"
    ExecDir="${Exec%/*}"

    # In case there is need to see the commands that are executed
    #set -x

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
}

DoPrintUsage() {
    echo "Usage: ${0##*/} [--error|--clean|--all] [FILEs...]"
}

DoProcessCommandLineArguments() {

    # No arguments: invalid
    if [ $# -eq 0 ]; then
        DoPrintUsage
        exit 1
    fi

    # One or more arguments
    while [ $# -gt 0 ]; do
        Arg="$1"
        shift

        case "$Arg" in
        -h|--help)
            DoPrintUsage
            exit 0
            ;;
        -e|--error)
            set -e
            ;;
        -c|--clean)
            rm -fr build/
            ;;
        -a|--all)
            for File in $(find src -name '*.[cC]'); do
                DoRunTest "$File"
            done
            ;;
        *)
            DoRunTest "$Arg"
            ;;
        esac
    done
}

DoProcessCommandLineArguments "$@"
