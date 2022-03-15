#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

# Constants
BuildScript="lib/scripts/build.mk"
CMOCKA_DIR="lib/cmocka"

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

DoBuildCmockaIfNecessary() {

    # Build cmocka if necessary
    if [ ! -f "$CMOCKA_DIR/build/src/libcmocka.so" ]; then
        (
            cd "$CMOCKA_DIR"
            mkdir build
            cd build
            cmake ..
            make
        )
    fi
}

DoRunTest() {

    # Arguments
    File="$1"

    # Determine file names and directories
    Exec="build/${File%.[cC]*}.elf"
    ExecDir="${Exec%/*}"

    # Create directories

    if [ ! -d "$ExecDir" ]; then
        mkdir -p "$ExecDir"
    fi

    DoBuildCmockaIfNecessary

    # Build test
    make -f $BuildScript \
        EXEC="$Exec" \
        INPUTS="$File" \
        CC=gcc \
        CFLAGS="-g -O0 -std=c99 -pedantic -Wall -Wextra -Werror --coverage" \
        CPPFLAGS="-D UNITTEST -I $CMOCKA_DIR/include" \
        LDFLAGS="--coverage -L $CMOCKA_DIR/build/src -l cmocka" \
        "$Exec"
    BuildResult=$?

    if [ $BuildResult -ne 0 ]; then
        # Update results
        DoUpdateResults $BuildResult
    else
        # Run test
        LD_LIBRARY_PATH=$CMOCKA_DIR/build/src "$Exec"
        TestResult=$?

        # Update results
        DoUpdateResults $TestResult
    fi
}

DoCoverageIfRequested() {
    if [ ! -z $FlagCoverage ]; then
        gcovr --filter="src/" --branch \
            --exclude-unreachable-branches \
            --exclude-throw-branches
        gcovr --filter="src/" | sed '1,4d'
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
