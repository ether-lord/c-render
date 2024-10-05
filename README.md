# c-render

## Instalation and running

1. Install dependencies
- CMake 3.14 or newer
- libglfw3-dev

2. Update `cglm` library submodule
```shell
git submodule init
git submodule update
```
OR

Pass `--recurse-submodules` when cloning the repository

3. Create and go to the `build` directory
```shell
mkdir build
cd build
```
4. Run CMake and build the source code
```shell
cmake ..
cmake --build .
```

5. Return to the project directory and run the executable file
```shell
cd ..
./build/main
```
