#!/bin/bash
set -e

# Navigate to the project root and then to the build directory
cd ..
echo "Current path after moving up: $(pwd)"
cd build
echo "Current path in build directory: $(pwd)"

# Build the project using CMake
echo "Starting build..."
cmake --build .
echo "Build completed."

# Run the ./testApp  executable
echo "Running ./testApp ..."
./testApp 

# Run the Python script to plot results
cd ..
cd scripts
echo "Running Python plotResults.py..."
python plotResults.py

echo "Script completed. Current path: $(pwd)"
