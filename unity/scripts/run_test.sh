#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

# Constants

BuildScript="lib/scripts/build.mk"
UNITY_DIR="lib/unity"
CMOCK_DIR="lib/cmock"
RunnerCreator="$UNITY_DIR/auto/generate_test_runner.rb"
MockCreator="$CMOCK_DIR/lib/cmock.rb"

BuildDir="build"
SrcDir="src"
TestsDir="tests"
TestsEnd="_test.[cC]*"
TestsObjDir="$BuildDir/obj_tests"
ObjDir="$BuildDir/obj"

# Variables
TestTotal=0
TestError=0
TestInexistent=0
ExitStatus=0

DoUpdateResults() {
    # == 0 Success
    # != 0 Error
    TestResult=$1

    # == 0 Test present
    # != 0 No test
    TestPresent=$2

    if [ $TestResult -ne 0 ]; then
        ExitStatus=1
        TestError=$((TestError + 1))
    fi

    if [ $TestPresent -ne 0 ]; then
        TestInexistent=$((TestInexistent + 1))
    fi

    TestTotal=$((TestTotal + 1))
}

DoPrintResults() {
    echo "=============================================="
    echo -n "$TestTotal Tests, "
    echo -n "$TestInexistent Inexistent, "
    echo -n "$TestError Failures"
    echo
    if [ $TestError -eq 0 ]; then
        echo "OK"
    else
        echo "FAIL"
    fi
    echo
}

DoBuildUnityIfNecessary() {
    # Do nothing
    :
}

DoBuildMocksIfNecessary() {
    Test="$1"

    MocksToCreate="$(
        sed -En '
            s/(^|.*\s)Auto-generate mock: (\S+(\s+\S+)*)(.*|$)/\2/p
        ' "$Test"
    )"

    (
        cd "$BuildDir/tests"

        for Header in $MocksToCreate; do
            HeaderName="${Header##*/}"
            Mocked="mocks/Mock$HeaderName"

            if [ ! -f "../../$Header" ]; then
                echo
                echo "Error generating mock: file '$Header' does not exit."
                echo
            elif [ ! -f "$Mocked" ] || [ "../../$Header" -nt "$Mocked" ]; then
                echo "Generating mock: file '$Header' -> '$Mocked'"
                ruby "../../$MockCreator" "../../$Header"
            fi
        done
    )
}

DetermineAdditionalFiles() {
    Test="$1"
    TestDir="${Test%/*}"

    ListOfFiles="$(
        sed -En '
            s/(^|.*\s)Also compile: (\S+(\s+\S+)*)(.*|$)/\2/p
        ' "$Test"
    )"

    AdditionalFiles=""

    for F in $ListOfFiles; do
        case "$F" in
        /*)
            # Absolute path
            AdditionalFiles="$AdditionalFiles $F"
            ;;
        *)
            # Relative path
            if [ -f "$F" ]; then
                # Found file based on current directory
                AdditionalFiles="$AdditionalFiles $F"
            elif [ -f "$TestDir/$F" ]; then
                # Found file based on test directory
                AdditionalFiles="$AdditionalFiles $TestDir/$F"
            else
                echo "Error: could not find file '$F'."
                exit 1
            fi
            ;;
        esac
    done
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

    if [ ! -f "$Test" ]; then
        # The test does NOT exist

        # Update results
        DoUpdateResults 0 1
    else
        # The test exists

        # Build test

        ASAN="-fsanitize=address -static-libasan" # Address sanitizer
        UBSAN="-fsanitize=undefined -fno-sanitize-recover" # Undefined behavior sanitizer

        CC="gcc"
        CFLAGS="-g -O0 -std=c90 -pedantic -Wall -Wextra -Wno-long-long --coverage $ASAN $UBSAN"
        CXX="g++"
        CXXFLAGS="-g -O0 -std=c++98 -pedantic -Wall -Wextra -Wno-long-long --coverage $ASAN $UBSAN"
        CPPFLAGS="-I include -I $BuildDir/tests -I $UNITY_DIR/src -I $CMOCK_DIR/src"
        LD="gcc"
        LDFLAGS="--coverage $ASAN $UBSAN"

        # Create test runner
        if [ ! -f "$Runner" ] || [ "$Test" -nt "$Runner" ]; then
            ruby $RunnerCreator "$Test" "$Runner"
        fi

        DoBuildUnityIfNecessary

        DoBuildMocksIfNecessary "$Test"

        DetermineAdditionalFiles "$Test"

        make -f $BuildScript \
            EXEC="$Exec" \
            OBJ_DIR="$TestsObjDir" \
            INPUTS="$File $Test $AdditionalFiles $Runner $UNITY_DIR/src/unity.c $CMOCK_DIR/src/cmock.c" \
            CC="$CC" \
            CFLAGS="$CFLAGS" \
            CXX="$CXX" \
            CXXFLAGS="$CXXFLAGS" \
            CPPFLAGS="$CPPFLAGS" \
            LD="$LD" \
            LDFLAGS="$LDFLAGS" \
            "$Exec"
        BuildResult=$?

        # Update results and return if building fails
        if [ $BuildResult -ne 0 ]; then
            DoUpdateResults $BuildResult 0
            return
        fi

        # Run test
        "$Exec"
        TestResult=$?

        # Update results
        DoUpdateResults $TestResult 0

        # Update results and return if testing fails
        if [ $TestResult -ne 0 ]; then
            DoUpdateResults $TestResult 0
            return
        fi
    fi

    # Build file

    CC="gcc"
    CFLAGS="-g -O0 -std=c90 -pedantic -Wall -Wextra -Werror -Wno-long-long"
    CXX="g++"
    CXXFLAGS="-g -O0 -std=c++98 -pedantic -Wall -Wextra -Werror -Wno-long-long"
    CPPFLAGS="-I include"
    LD="gcc"
    LDFLAGS=""

    make -f $BuildScript \
        OBJ_DIR="$ObjDir" \
        INPUTS="$File" \
        CC="$CC" \
        CFLAGS="$CFLAGS" \
        CXX="$CXX" \
        CXXFLAGS="$CXXFLAGS" \
        CPPFLAGS="$CPPFLAGS" \
        LD="$LD" \
        LDFLAGS="$LDFLAGS" \
        "$Object"
    BuildResult=$?

    # Update results and return if building fails
    if [ $BuildResult -ne 0 ]; then
        DoUpdateResults $BuildResult 0
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
            for File in $(find $SrcDir/ -name '*.[cC]*'); do
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
