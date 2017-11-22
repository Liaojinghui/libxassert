xassert
=======

A simple assertion libraries that I use, which prints the values that failed the assertion.

`xassert` is easily importable into CMake projects using either `add_subdirectory` (when not installed on the system but present locally in the code repository that's importing it) or using `find_package` (when installed on the system).

## Build

    mkdir build/
    cd build/
    cmake ..
    cmake --build .
    cmake --build . --target install    
