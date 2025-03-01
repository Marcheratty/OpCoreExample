
# Create OpCore as an INTERFACE library
add_library(OpCore INTERFACE)

# Set include directories so that headers are found for OpCore
target_include_directories(OpCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add KalmanFusion as a STATIC library
add_library(KalmanFusion STATIC src/Filters/KalmanFusion.cpp)
target_include_directories(KalmanFusion PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


##################################
# For testing
##################################

# Add Google Test
#find_package(GTest REQUIRED)
#Sinclude_directories(${GTEST_INCLUDE_DIRS})

# Add the test files for the test_runner executable
#add_executable(test_runner test/test_matrix.cpp test/test_vector.cpp)

# Ensure the test directory can find the OpCore headers
#target_include_directories(test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link Google Test libraries and gtest_main to provide the main function
#target_link_libraries(test_runner ${GTEST_LIBRARIES} pthread gtest_main)

# Enable testing for the project
#enable_testing()
