[![Build Status][github_status]][github_link]
[![Build Status][travis_status]][travis_link]

[github_status]: https://github.com/Mizux/match3/workflows/C++%20CI/badge.svg
[github_link]: https://github.com/Mizux/match3/actions

[travis_status]: https://travis-ci.com/Mizux/match3.svg?branch=master
[travis_link]: https://travis-ci.com/Mizux/match3

# Introduction
Some Match-3 stuff in C++/Qt, work in progress...

# Project directory layout
Thus the project layout is as follow:

* [CMakeLists.txt](CMakeLists.txt) Top-level for [CMake](https://cmake.org/cmake/help/latest/) based build.
* [cmake](cmake) Subsidiary CMake files.

* [ci](ci) Top-level directory for Makefile/docker CI.

# C++ Project Build
To build the C++ project, as usual:
```sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target all
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build --config Release --target test
```
