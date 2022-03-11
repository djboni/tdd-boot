# [TDD CppUTest](https://github.com/djboni/tdd-cpputest)

Copyright (c) 2022 Djones A. Boni

This project helps you to start a C/C++ project with TDD (Test Driven
Deveoplment) using [CppUTest](https://github.com/cpputest/cpputest).

You are free to copy, modify, and distribute **TDD CppUTest** with attribution
under the terms of the MIT license. See the LICENSE file for details.

## Cloning this project

1. Clone and initializing the submodules

```sh
git clone --recurse-submodules https://github.com/djboni/tdd-cpputest
```

If you cloned without `--recurse-submodules`, you can manually initialize the
submodules

```sh
git submodule init
git submodule update
```

2. Execute the tests

```sh
sh scripts/run_test.sh --all
```

This script must be executed from the project root.

## Dependencies

Necessary:

- Bash Shell
- Make
- G++

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

## Example

```c
/* File: example.c with additional comments. */

/* Normal source code. It is always compiled. */

#include <stdint.h>

int32_t Sum(int32_t x, int32_t y)
{
    return x + y;
}

/* Unit-test section. It is compiled only when the macro UNITTEST is defined. */

#ifdef UNITTEST
    #include "CppUTest/TestHarness.h"

TEST_GROUP (Sum)
{
    /* Test set-up: runs before each test. */
    void setup() {}

    /* Test tear-down: runs after each test. */
    void teardown() {}
};

/*
 * Test naming convention:
 *
 * - TEST(Function, Parameters_ExpectedResult) (function)
 * - TEST(Context, Interaction_ExpectedReaction) (system)
 * - TEST(Given, When_Then) (analogy to Cucumber scenarios)
 */

TEST(Sum, ZeroZero_ReturnZero)
{
    LONGS_EQUAL(0, Sum(0, 0));
}

TEST(Sum, OneZero_ReturnOne)
{
    LONGS_EQUAL(1, Sum(1, 0));
}

TEST(Sum, ZeroOne_ReturnOne)
{
    LONGS_EQUAL(1, Sum(0, 1));
}

TEST(Sum, OneOne_ReturnTwo)
{
    LONGS_EQUAL(2, Sum(1, 1));
}

TEST(Sum, ThreeFive_ReturnEight)
{
    LONGS_EQUAL(8, Sum(3, 5));
}

#endif /* UNITTEST */

```
