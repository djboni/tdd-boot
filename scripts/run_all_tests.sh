#!/bin/sh
# Copyright (c) 2022 Djones A. Boni - MIT License

set -e

# Constants
RunTest="scripts/run_test.sh"

# Find C files and run their tests
for File in $(find src -name '*.[cC]'); do
    sh $RunTest "$File"
done
