#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

# Constants

BuildScript="lib/scripts/build.mk"
UNITY_DIR="lib/unity"
RunnerCreator="$UNITY_DIR/auto/generate_test_runner.rb"

BuildDir="build"
SrcDir="src"
TestsDir="tests"
TestsEnd="_test.[cC]*"
TestsObjDir="$BuildDir/obj_tests"
ObjDir="$BuildDir/obj"

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

DoBuildUnityIfNecessary() {
    # Do nothing
    :
}

DoRunTest() {

    # Arguments
    File="$1"

    Test="$(echo $File | sed -E "s:($SrcDir)/(.*)(\.[cC].*):$TestsDir/\2$TestsEnd:")"
    Test="$(ls -1 $Test | head -n 1)"

    # Determine file names and directories

    Runner="$BuildDir/${Test%.[cC]*}_runner.c"
    RunnerDir="${Runner%/*}"

    Exec="$BuildDir/${File%.[cC]*}.elf"
    ExecDir="${Exec%/*}"

    Object="$ObjDir/${File%.[cC]*}.o"
    ObjectDir="${Object%/*}"

    # Create directories

    if [ ! -d "$RunnerDir" ]; then
        mkdir -p "$RunnerDir"
    fi

    if [ ! -d "$ExecDir" ]; then
        mkdir -p "$ExecDir"
    fi

    if [ ! -d "$ObjectDir" ]; then
        mkdir -p "$ObjectDir"
    fi

    # Build file

    CC="gcc"
    CFLAGS="-g -O0 -std=c90 -pedantic -Wall -Wextra -Werror -Wno-long-long"
    CXX="g++"
    CXXFLAGS="-g -O0 -std=c++98 -pedantic -Wall -Wextra -Werror -Wno-long-long"
    CPPFLAGS="-I include"
    LDFLAGS=""

    make -f $BuildScript \
        OBJ_DIR="$ObjDir" \
        INPUTS="$File" \
        CC="$CC" \
        CFLAGS="$CFLAGS" \
        CXX="$CXX" \
        CXXFLAGS="$CXXFLAGS" \
        CPPFLAGS="$CPPFLAGS" \
        LDFLAGS="$LDFLAGS" \
        "$Object"
    BuildResult=$?

    # Update results and return if building fails
    if [ $BuildResult -ne 0 ]; then
        DoUpdateResults $BuildResult
        return
    fi

    # If the test exists
    if [ -f "$Test" ]; then

        # Build test

        CC="gcc"
        CFLAGS="-g -O0 -std=c90 -pedantic -Wall -Wextra -Werror -Wno-long-long --coverage"
        CXX="g++"
        CXXFLAGS="-g -O0 -std=c++98 -pedantic -Wall -Wextra -Werror -Wno-long-long --coverage"
        CPPFLAGS="-I include -I $UNITY_DIR/src"
        LDFLAGS="--coverage"

        # Create test runner
        if [ ! -f "$Runner" ] || [ "$Test" -nt "$Runner" ]; then
            ruby $RunnerCreator "$Test" "$Runner"
        fi

        DoBuildUnityIfNecessary

        make -f $BuildScript \
            EXEC="$Exec" \
            OBJ_DIR="$TestsObjDir" \
            INPUTS="$File $Test $Runner $UNITY_DIR/src/unity.c" \
            CC="$CC" \
            CFLAGS="$CFLAGS" \
            CXX="$CXX" \
            CXXFLAGS="$CXXFLAGS" \
            CPPFLAGS="$CPPFLAGS" \
            LDFLAGS="$LDFLAGS" \
            "$Exec"
        BuildResult=$?

        # Update results and return if building fails
        if [ $BuildResult -ne 0 ]; then
            DoUpdateResults $BuildResult
            return
        fi

        # Run test
        "$Exec"
        TestResult=$?

        # Update results
        DoUpdateResults $TestResult
    fi
}

DoCoverageIfRequested() {
    if [ ! -z $FlagCoverage ]; then
        gcovr --filter="$SrcDir/" --filter="\.\./code/$SrcDir/" --branch \
            --exclude-unreachable-branches \
            --exclude-throw-branches
        gcovr --filter="$SrcDir/" --filter="\.\./code/$SrcDir/" | sed '1,4d'
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
            rm -fr "$BuildDir"
            ;;
        -r|--coverage)
            FlagCoverage=1
            ;;
        -a|--all)
            for File in $(find src/ -name '*.[cC]*'); do
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
