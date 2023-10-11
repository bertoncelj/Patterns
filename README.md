## Usage

Please note that the commands have to be executed from the `build` subdirectory.

| command                         | action                  | &nbsp;                                                              |
| ------------------------------- | ----------------------- | ------------------------------------------------------------------- |
| `cmake --preset=simple`         | buildsystem from preset | &nbsp;                                                              |
| `cmake -G "MinGW Makefiles" ..` | generate buildsystem    | &nbsp;                                                              |
| `make`                          | compile source code     | executable can be found under [build/src/](build/src/)              |
| `make test`                     | run cmocka tests        | &nbsp;                                                              |
| `make doc`                      | generate documentation  | to view open [build/doc/html/index.html](build/doc/html/index.html) |
| `make clean`                    | remove compiled files   | &nbsp;                                                              |

If VSCode is used these commands are also available as tasks in [tasks.json](.vscode/tasks.json).

## Building

First, clone this repo and do the preliminary work:

- Simulation for developer

```shell
cd Build
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_WARNINGS=ON -DENABLE_WARNINGS_AS_ERRORS=ON -G "MinGW Makefiles" ..
cmake --build . --config Release --target main
./Simulation
```

- Simulation using presets

Go to root dir:

```shell
cmake --preset=simple
cd Build
make
```

- Documentation

```shell
cd Build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target docs
```

## Software Requirements

- CMake 3.22+
- GNU Makefile
- MSVC 2017 (or higher), GCC 9 (or higher), Clang 9 (or higher)
- Doxygen
- Code Coverage (only on GNU|Clang): lcov, gcovr
