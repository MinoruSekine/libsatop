# libsatop

libsatop is a Library for saturated arithmetic operation by C++11.

![](https://github.com/MinoruSekine/libsatop/workflows/Check%20build/badge.svg?branch=main)

## API Reference

- [By Doxygen](https://minorusekine.github.io/libsatop/Doxygen/html/)

## Integrate into your project

1. Include header files in libsatop/include/
1. Add libsatop/include/ into your include path.
1. Compile your codes

It is not necessary to build and link static link library of libsatop
because all implementations are available in header files.

## Usage

## Build samples and unit tests

Makefile of libsatop will provide followings on your environments

- Build and run unit tests
- Build and run sample programs
- Some checks
  - Coding rule check by cpplint
  - Static analysis by cppcheck
- Build documents with Doxygen

### List of build targets

| `make` target | How it works |
----|----
| `all` | Same as `build-all` |
| `build-all` | `build-sample` and `build-test` |
| `build-sample` | Build sample programs |
| `build-test` | Build unit tests |
| `check` | Process `cppcheck` and `cpplint` |
| `clean` | Remove generated files |
| `coverage` | Create coverage report into out/site/coverage (Must use with `BUILD_TYPE=coverage`) |
| `cppcheck` | Static analytics by `cppcheck` |
| `cpplint` | Lint by `cpplint` |
| `doc` | `coverage` and `doxygen` |
| `doxygen` | Generate doxygen HTML documents into out/site/Doxygen |
| `latex` | Generate doxygen LaTeX documents into out/site/Doxygen |
| `pdf` | Generate doxygen PDF documents into out/site/Doxygen |
| `run-all` | `run-sample` and `run-test` |
| `run-sample` | Build (if necessary) and run sample programs |
| `run-test` | Build (if necessary) and run unit tests |
| `site` | Build tree for [project site](https://minorusekine.github.io/libsatop/) |

### Build options

#### `BUILD_TYPE`

| `BUILD_TYPE` | How it works |
----|----
| `debug` | All optimizations are disabled in build |
| `release` | Optimizations are enabled in build |
| `coverage` | Options for build `coverage` as `make` target |

- In `coverage`, optimization are disabled
  and some additional information
  to get coverage report will be generated

### Build and run unit tests

1. Install [Google Test](https://github.com/google/googletest)
1. `make run-test` in this directory

#### Build coverage report

1. Install `gcovr`
1. `make BUILD_TYPE=coverage coverage`,
   so html report is put into `out/coverage_html/`

### Build and run sample programs

1. `make run-sample` in this directory

### Checks

Some check targets are available in build by Makefile

#### cpplint

- Install `cpplint.py`
- Set that directory in your environment variable `PATH`
- `make cpplint`

or

- `make CPPLINT=your/installed/directory/cpplint.py cpplint`

#### cppcheck

- Install `cppechck` into your environment
- `make cppcheck`

### Generate Doxygen document files

- Install `doxygen` into your environment
- `make doc`

### For Windows (Visual Studio)

- The solution file to build samples and tests with Visual Studio
  is available as build/win_vs/libsatop/libsatop.sln
- Google Test Framework will be recovered automatically
  at opening solution file

## Environments

As of 2021/04/17,
all tests succeed and all samples are working well on following environments

| OS | Compiler |
----|----
| FreeBSD 12.2-STABLE | clang++ |
| macOS Catalina 10.15.7 | g++ (symlink to clang) |
| Ubuntu 16.04 | g++ |
| Ubuntu 18.04 | g++ |
| Windows Server 2016 Datacenter | Visual C++ |
