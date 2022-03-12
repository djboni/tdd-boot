#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

# Constants
BuildScript="lib/scripts/build.mk"
RunnerCreator="lib/unity/auto/generate_test_runner.rb"

# Variables
TestTotal=0
TestError=0
ExitStatus=0

DoUpdateResults() {
    # == 0 Success
    # != 0 Error
    TestResult=$1

    if [ $TestResult -ne 0 ]; then
        ExitStatus=1
        TestError=$((TestError + 1))
    fi
    TestTotal=$((TestTotal + 1))
}

DoPrintResults() {
    echo "=============================================="
    echo "$TestTotal Tests, $TestError Failures"
    if [ $TestError -eq 0 ]; then
        echo "OK"
    else
        echo "FAIL"
    fi
}

DoBuildCppUTestIfNecessary() {

    # Build CppUTest if necessary
    if [ ! -f lib/cpputest/cpputest_build/lib/libCppUTest.a ]; then
        (
            cd lib/cpputest/cpputest_build
            autoreconf .. -i
            ../configure
            make
        )
    fi
}

DoRunTest() {

    # Arguments
    File="$1"

    # Determine file names and directories
    Runner="build/${File%.[cC]}_runner.c"
    RunnerDir="${Runner%/*}"
    Exec="build/${File%.[cC]*}.elf"
    ExecDir="${Exec%/*}"

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
        CFLAGS="-g -O0 -std=c90 -pedantic -Wall -Wextra -Werror --coverage" \
        CPPFLAGS="-D UNITTEST -I lib/unity/src" \
        LDFLAGS="--coverage" \
        "$Exec"

    # Run test
    "$Exec"
    TestResult=$?

    # Update results
    DoUpdateResults $TestResult
}

DoCoverageIfRequested() {
    if [ ! -z $FlagCoverage ]; then
        gcovr --exclude="lib/" --exclude="build/" --branch
        gcovr --exclude="lib/" --exclude="build/" | sed '1,4d'
    fi
}

DoPrintUsage() {
    echo "Usage: ${0##*/} [--exec|--error|--clean|--coverage|--all] [FILEs...]"
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
        -x|--exec)
            # In case there is need to see the commands that are executed
            set -x
            ;;
        -e|--error)
            # Set error flag to stop on first error
            set -e
            ;;
        -c|--clean)
            rm -fr build/
            ;;
        -r|--coverage)
            FlagCoverage=1
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

    DoCoverageIfRequested
    DoPrintResults
    exit $ExitStatus
}

DoProcessCommandLineArguments "$@"
