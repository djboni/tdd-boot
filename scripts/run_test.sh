#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

# Constants
BuildScript="lib/scripts/build.mk"

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
        CPPFLAGS="-D UNITTEST -I lib/cpputest/include" \
        LDFLAGS="--coverage -l CppUTest -L lib/cpputest/cpputest_build/lib" \
        "$Exec"

    # Run test
    "$Exec"
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
}

DoProcessCommandLineArguments "$@"
