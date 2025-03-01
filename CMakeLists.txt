cmake_minimum_required(VERSION 3.16)
project(testOpCore LANGUAGES CXX)

# Add OpCore as a subdirectory
add_subdirectory(opcore)

# Create the test executable
add_executable(testApp src/main.cpp)

# Link OpCore (since it's INTERFACE, this just adds include directories)
target_link_libraries(testApp PRIVATE OpCore KalmanFusion)
