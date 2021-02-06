TITLE build
rmdir /s /q build
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake .. 
cmake --build .
pause
