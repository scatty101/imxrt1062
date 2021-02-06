# I.MX RT1062

CMake based drivers and utilities for i.MX RT1062

## Tests

Tests based on Google tests

## Build

On windows You can use build.bat. Otherwise

```
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
cmake --build .
```

## Toolchain

Used toolchain:

```
arm-none-eabi-gcc (GNU Tools for Arm Embedded Processors 9-2019-q4-major) 9.2.1 20191025 (release) [ARM/arm-9-branch revision 277599]
```
