# [TDD Boot](https://github.com/djboni/tdd-boot)

Copyright (c) 2022 Djones A. Boni

This project helps you to start a C/C++ project with TDD (Test Driven
Development) using different unit-test frameworks.

The available examples are:

- [Unity (C)](https://github.com/ThrowTheSwitch/Unity)
- [cmocka (C)](https://gitlab.com/cmocka/cmocka)
- [CppUTest (C++)](https://github.com/cpputest/cpputest)
- [Boost.Test (C++)](http://www.boost.org/doc/libs/release/libs/test)

You are free to copy, modify, and distribute **TDD Boot** with attribution
under the terms of the MIT license. See the LICENSE file for details.

## Cloning this project

1. Clone

```sh
git clone https://github.com/djboni/tdd-boot
```

2. Checkout one of the frameworks

```sh
git checkout cpputest
# OR
git checkout unity
git checkout cmocka
git checkout boosttest
# ETC
```

3. Initialize the submodules

```sh
git submodule update --init
```

3. Execute the tests

```sh
sh scripts/run_test.sh --all
```

This script must be executed from the example directory root.

## Organization

For each test framework directory:

1. The directory _src/_ has the source files. Source files are named
   X.c or X.cpp.
2. The directory _include/_ has the header files. Header files are named
   X.h.
3. The directory _tests/_ has the test files. Test files are named
   X_test.c or X_test.cpp.
4. The directory _lib/_ has the libraries used.
5. The directory _scripts/_ has scripts and other supporting files.

# Running tests

In the framework directory:

1. If you want to run all tests use `--all`
   - `sh scripts/run_test.sh --all`
2. If you want to see the test coverage after the test use `--coverage`
   - `sh scripts/run_test.sh --all --coverage`
3. If you want to run test only for some source files just pass the filenames
   (use the files from _src/_, not from _tests/_)
   - `sh scripts/run_test.sh src/FILE.c`

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
