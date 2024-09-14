# FTowerX

An implementation of the Tower of Hanoi game, following best practices.

This is a cross-platform, lightweight, terminal-based implementation of the Tower
of Hanoi, featuring automated testing, coverage reports, packaging, and more. It
also includes generated library files that you can link to create custom user
interfaces or extend the current implementation with ease.

<p align="center"><img src="https://github.com/user-attachments/assets/a526319b-3c7a-4442-8e88-ed85eb45a4d1" alt="FTowerX"></img></p>

1. [Executable and Library](#executable-and-library)
2. [Installation and Packaging](#installation-and-packaging)
3. [Tests and Coverage Reports](#tests-and-coverage-reports)
4. [Documentation](#documentation)
5. [Extending](#extending)

## Executable and Library

This project uses the [SeeMake](https://github.com/MhmRhm/SeeMake) template. To
build it on either Windows or Linux, you need to install the required packages
and software first. For Linux instructions, see
[here](https://github.com/MhmRhm/SeeMake?tab=readme-ov-file#setting-up-linux),
and for Windows setup, follow
[these](https://github.com/MhmRhm/SeeMake?tab=readme-ov-file#setting-up-windows)
instructions.

After installing the dependencies, use the following commands to build all the
artifacts, run tests, and create installers:

```bash
# On Linux
cmake --workflow --preset linux-default-release

# On Windows
cmake --workflow --preset windows-clang-release
# or
cmake --workflow --preset windows-default-release
```

You should see the following message after the build:

> 100% tests passed, 0 tests failed out of 21

## Installation and Packaging

On Linux, you should also see the following message indicating that the
installation package was successfully created:

> CPack: - package: /repos/FTowerX-build-linux-default-release/package-linux-deb/FTowerX-0.0.0-Linux.deb generated.

On Windows, the following success message will appear:

> CPack: - package: C:/Users/Mohammad Rahimi/Documents/FTowerX-build-windows-clang-release/package-windows-nsis/FTowerX-0.0.0-win64.exe generated.

You can use the generated installers to install the game, or use CMake to install
it:

```bash
cmake --install <build-directory> --prefix <installation-directory>
```

This is how your `installation-directory` will look:

```bash
tree ../installation-directory/

# ../installation-directory/
# ├── bin
# │   └── toh
# ├── include
# │   └── toh
# │       └── toh_model.h
# └── lib
#     ├── libtoh.a
#     ├── libtoh.so
#     └── toh
#         └── cmake
#             ├── TohConfig.cmake
#             ├── TohLibrary.cmake
#             └── TohLibrary-release.cmake
#
# 7 directories, 7 files
```

## Tests and Coverage Reports

During the build process, tests will run automatically. To generate coverage
reports, run these commands:

```bash
# On Linux
# For the library
cmake --build --preset linux-default-debug --target coverage-google_test_libtoh
# For the executable
cmake --build --preset linux-default-debug --target coverage-google_test_toh

# On Windows
# For the library
cmake --build --preset windows-clang-debug --target coverage-google_test_libtoh
# For the executable
cmake --build --preset windows-clang-debug --target coverage-google_test_toh
```

You should see the coverage output in the terminal:

> Overall coverage rate:  
lines......: 91.4% (32 of 35 lines)  
functions......: 75.0% (6 of 8 functions)  

Coverage reports are also available in HTML format. Navigate to the report
subdirectory in the build directory and run the following command:

```bash
python -m http.server <port-number>
```

Python will serve the report in your browser, or you can simply open the
`index.html` file in your browser.

<p align="center"><img src="https://i.postimg.cc/YC7PZ9z2/temp-Imagec-RDRIB.avif" alt="FTowerX-Coverage"></img></p>

## Documentation

Doxygen documentation can also be generated similarly to the coverage reports:

```bash
# On Linux
# For the library
cmake --build --preset linux-default-release --target doxygen-libtoh_static
# For the executable
cmake --build --preset linux-default-release --target doxygen-terminal_toh_static

# On Windows
# For the library
cmake --build --preset windows-clang-release --target doxygen-libtoh_static
# For the executable
cmake --build --preset windows-clang-release --target doxygen-terminal_toh_static
```

<p align="center"><img src="https://i.postimg.cc/15wTv66Y/temp-Image-Oivazx.avif" alt="FTowerX-Documentation"></img></p>

## Extending

You can link your projects to this one by following these steps:

1. Use CMake's FetchContent to retrieve this project. Your `CMakeLists.txt` file
might look like this:

```cmake
cmake_minimum_required(VERSION 3.30.0)
project(Extension VERSION 0.0.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(LibToh
    GIT_TAG main
    GIT_REPOSITORY https://github.com/MhmRhm/FTowerX.git
)
FetchContent_MakeAvailable(LibToh)

add_executable(extension main.cpp)
target_link_libraries(extension PRIVATE toh::precompiled toh::libtoh_shared)
```

2. Create a `.cpp` file containing the `main` function:

```cpp
#include <iostream>
#include <format>
#include "libtoh/toh_model.h"

int main() {
  using Play = std::vector<toh::Position>;

  toh::Game game{10};
  Play plays{};
  solveToh(plays, 10, toh::Left, toh::Middle, toh::Right);

  std::cout << std::format("game.isFinished() = {}", game.isFinished())
            << std::endl;

  for (auto &&play : plays) {
    game.select(play);
  }

  std::cout << std::format("game.isFinished() = {}", game.isFinished())
            << std::endl;
}
```

3. To simplify things, copy the `CMakePresets.json` file from this project into
yours. Then run the build command:

```bash
cmake --workflow --preset linux-default-debug
```

Now, you should be able to run your program:

> game.isFinished() = false  
game.isFinished() = true
