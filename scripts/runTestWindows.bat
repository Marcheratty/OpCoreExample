@echo off
setlocal enabledelayedexpansion

REM Move up one directory (from the current folder, assumed to be a subfolder)
cd ..
echo Current path after moving up: %cd%

REM Enter the build directory
cd build
echo Current path in build directory: %cd%

REM Build the project using CMake
echo Starting build...
cmake --build .
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)
echo Build completed.

REM Run the TelemetryExec executable
echo Running TelemetryExec...
TelemetryExec.exe
if errorlevel 1 (
    echo TelemetryExec failed.
    pause
    exit /b 1
)

REM Run the Python script to plot results
echo Running Python plotResults.py...
python plotResults.py
if errorlevel 1 (
    echo Python script failed.
    pause
    exit /b 1
)

echo Script completed. Current path: %cd%
pause
