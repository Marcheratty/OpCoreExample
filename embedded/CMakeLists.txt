cmake_minimum_required(VERSION 3.16)
project(KalmanTest LANGUAGES C)

# Add static library for matrix handling
add_library(MatrixHandler STATIC src/Matrix.c)
add_library(VectorHandler STATIC src/Vector.c)

target_include_directories(MatrixHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(VectorHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the test executable
add_executable(KalmanTest test.c)

# Link libraries
target_link_libraries(KalmanTest PRIVATE MatrixHandler VectorHandler)
