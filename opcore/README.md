
# Clone

``` bash
git submodule add https://github.com/Marcheratty/OpCore.git OpCore
git submodule update --init --recursive
```


# CMake include

``` CMakeLists.txt
# Default setup
cmake_minimum_required(VERSION 3.16)
project(testOpCore LANGUAGES CXX)

# Add OpCore as a subdirectory
add_subdirectory(OpCore)

# Create the test executable
add_executable(testApp src/main.cpp)

# Link OpCore (since it's INTERFACE, this just adds include directories)
target_link_libraries(testApp PRIVATE OpCore KalmanFusion)
```

# Includes

``` c++
#include <OpCore/Matrix.h>
#include <OpCore/Vector.h>
#include <Filters/KalmanFusion.h>

```
