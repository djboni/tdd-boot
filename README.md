# [TDD Boot](https://github.com/djboni/tdd-boot)

Copyright (c) 2022 Djones A. Boni

This project helps you to start a C/C++ project with TDD (Test Driven
Development) using different unit-test frameworks.

The available examples are:

- Unity (C)
- cmocka (C)
- CppUTest (C++)

You are free to copy, modify, and distribute **TDD Boot** with attribution
under the terms of the MIT license. See the LICENSE file for details.

## Cloning this project

1. Clone and initializing the submodules

```sh
git clone --recurse-submodules https://github.com/djboni/tdd-boot
```

If you cloned without `--recurse-submodules`, you can manually initialize the
submodules

```sh
git submodule init
git submodule update
```

2. Enter one of the example directories

```sh
cd CppUTest
# OR
cd Unity
cd cmocka
# ETC
```

3. Execute the tests

```sh
sh scripts/run_test.sh --all
```

This script must be executed from the example directory root.

## Dependencies

Necessary:

- Bash Shell
- Make
- GCC/G++
- Ruby (for Unity)
- Cmake (for cmocka)

Optional:

- Gcovr
- Clang-format
- Python
- Pre-commit

## How to use

1. Enter _src_ directory copy, rename and edit a file and run the tests.
2. If you want to run all tests use `--all`
   - `sh scripts/run_test.sh --all`
3. If you want to run test only some files use the filenames
   - `sh scripts/run_test.sh FILE.c`
4. If you want to see the test coverage after the test use `--coverage`
   - `sh scripts/run_test.sh --all --coverage`
5. See the example below:
   - A normal source code (with includes, variables, and functions).
   - Then there is the unit-test section, with set-up, tear-down, and test
     functions which is used to test the functions in the file.
