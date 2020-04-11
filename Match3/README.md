# Match3 {#mainpage}
[TOC]

# Introduction {#match3_intro}

Match3 engine library using C++11.

# Coding Standard {#match3_coding}
This section contains some general guidelines on arranging files.

The source code is organize as folllow:  
- **doc**: Meta doxygen documentation files (i.e. .dox .md).
- **include**: Public header files (i.e. .hpp .hxx).
- **src**: Implementation files (i.e. .cpp, _p.cpp, _p.hpp).
- **test**: Unit test files.
- **build**: Build directory.
  - **lib**: Library generated files (i.e. .so).
  - **bin**: Binary generated files.
  - **doc/Match3**: Documentation generated files.

The implementation and public header files should appear in separate
directory.

## Code Formating {#match3_formating}
Please look at the .clang-format file at the root of the project.  
To use it, you can use the following command (i.e. put it in a bash function).
```sh
find . -not -path "*/build/*" -type f \( -iname "*.[hc]pp" -or -iname "*.hxx" \) \
-exec echo "Formatting {}" \; -exec clang-format -style=file -i {} \;
```

# HowTo Build {#match3_build}
## Dependencies {#match3_deps}
Project use CMake >= 3.2, C++11.

To install new cmake version on *old* Ubuntu (i.e. < 16.04) just retrieve a new version on ppa.
```sh
sudo add-apt-repository ppa:george-edison55/cmake-3.x -y
sudo apt-get update -qq
sudo apt-get install -qq build-essential cmake
```
otherwise juste use:
```sh
sudo apt-get install -qq build-essential cmake
```

## Native Build {#match3_cmake}
To build:
```sh
mkdir build && cd build
cmake ..
make
```

# Documentation {#match3_doc}
You can also build the **USEFULL** documentation:  
```sh
mkdir build && cd build
cmake -DENABLE_DOC=ON ..
make Match3_doc
```

and display it with:  
```sh
chromium doc/Match3/html/index.html
```

# Scoring {#match3_scoring}
Please look at [Scoring](doc/Scoring.md).

# Misc {#match3_misc}
Test plan images are generated using [plantuml](http://plantuml.com/).
To regenerate it, you can use:
```sh
java -jar plantuml.jar -Tpng *.pu
```
