#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

# Constants
BuildScript="lib/scripts/build.mk"
CPPUTEST_DIR="lib/cpputest"

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
    if [ ! -f "$CPPUTEST_DIR/cpputest_build/lib/libCppUTest.a" ]; then
        (
            cd "$CPPUTEST_DIR/cpputest_build"
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
    Exec="build/${File%.[cC]*}.elf"
    ExecDir="${Exec%/*}"

    # Create directories

    if [ ! -d "$ExecDir" ]; then
        mkdir -p "$ExecDir"
    fi

    DoBuildCppUTestIfNecessary

    # Build test
    make -f $BuildScript \
        EXEC="$Exec" \
        INPUTS="$File scripts/main.c" \
        CC=g++ \
        CFLAGS="-g -O0 -std=c++98 -pedantic -Wall -Wextra -Werror -Wno-long-long --coverage" \
        CXX=g++ \
        CXXFLAGS="-g -O0 -std=c++98 -pedantic -Wall -Wextra -Werror -Wno-long-long --coverage" \
        CPPFLAGS="-D UNITTEST -I $CPPUTEST_DIR/include" \
        LDFLAGS="--coverage -l CppUTest -L $CPPUTEST_DIR/cpputest_build/lib" \
        "$Exec"

    # Run test
    "$Exec"
    TestResult=$?

    # Update results
    DoUpdateResults $TestResult
}

DoCoverageIfRequested() {
    if [ ! -z $FlagCoverage ]; then
        gcovr --filter="src/" --branch
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
            for File in $(find src -name '*.[cC]' -or -name '*.[cC][pP][pP]'); do
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
